//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/lock_file.cc
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
/// 
/// @brief A common class used to provide safe file locking semantics, even
/// over network file systems (like NFS).
/// 
/// @copyright National Robotics Engineering Center, Carnegie Mellon University
/// @copyright 10 40th Street, Pittsburgh, PA 15201
/// @copyright www.rec.ri.cmu.edu
///  
/// @copyright Control Instructions (who can see this code):
/// @copyright NREC Confidential.  Not for public release unless permission granted
/// @copyright by program manager.
///  
/// @copyright Usage Rights (who can use this code):
/// @copyright Usage allowed for all NREC programs with permissions from author and
/// @copyright program manager.
///  
/// @copyright This notice must appear in all copies of this file and its derivatives.
///  
/// History of Significant Contributions (don't put commit logs here):
///     2013-08-21    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <hub/base/platform/system_metrics.hh>
#include <hub/base/platform/process.hh>
#include <hub/base/platform/threads.hh>

#include <hub/base/status_exception.hh>
#include <hub/base/timer.hh>
#include <hub/base/guid.hh>

#include <filesystem/lock_file.hh>

#include <hub/utility/string.hh>

//
// Everything we do here is in the filesystem namespace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

lock_file::lock_file()
{
}

/*
 * ################################################################################################
 */

lock_file::lock_file (
                       const path &lock_base_path,
                       double acquire_timeout,
                       double reap_timeout
                     )
                     :
                     base_path(lock_base_path)
{
    //
    // Lock the file.
    //

    lock(acquire_timeout, reap_timeout);
}

/*
 * ################################################################################################
 */

lock_file::~lock_file()
{
    //
    // This just unlocks the file (assuming it is still locked).
    //

    if(is_locked() == true)
    {
        unlock();
    }
}

/*
 * ################################################################################################
 */

void lock_file::lock (
                       double acquire_timeout,
                       double reap_timeout
                     )
{

    //
    // We retry this operation a few times until we are successful.
    //

    hub::base::timer timeout;

    while(acquire_timeout < 0.0 || timeout.get_elapsed_time() < acquire_timeout)
    {
        //
        // From now on we have to try/catch the rest of these operations,
        // as they can fall.
        //

        try
        {
            if (is_locked() == false)
            {
                // Try to create a new lock, this will throw an exception if the 
                // file already exists meaning the lock is present
                refresh_path(true);
            } else
            {
                //
                // Hit a problem early on -- somebody else probably already
                // as this lock!! Let's read the contents and see how old it is.
                //
                try_break_lock(reap_timeout);

                // We broke the lock, should be good to refresh it
                refresh_path(true);
            }
        }
        catch(const hub::base::status_exception&)
        {

            //
            // Either way, we want to keep trying to break it. Sleep a bit
            // and try again.
            //

            hub::base::sleep(0.010);
            continue;
        }

        //
        // We have the lock at this point (the open call would not have
        // passed otherwise). We can now move on.
        //

        return;

    }

    //
    // If we got here, then we failed to acquire a lock. Bail.
    //

    throw hub::base::status_exception("Failed to acquire the lock file (%s) within the timeout.", base_path.c_str());
}

/*
 * ################################################################################################
 */

void lock_file::unlock()
{
    //
    // Are we already locked?
    //

    if(is_locked() == false)
    {
        throw hub::base::status_exception("Tried to unlock an already unlocked file (%s).", base_path.c_str());
    }

    //
    // Delete the base lock file -- we are done with it.
    //

    base_path.remove();

}

/*
 * ################################################################################################
 */

void lock_file::refresh_lock()
{
    //
    // Are we already locked?
    //

    if(is_locked() == false)
    {
        throw hub::base::status_exception("Tried to refresh a lock file that is not locked (%s).", base_path.c_str());
    }

    refresh_path(false);

}

/*
 * ################################################################################################
 */

void lock_file::try_break_lock (
                                 double reap_timeout
                               )
{
    //
    // Try to read content from the base path. This will
    // be the timestamp that they originally wrote out.
    //

    std::string data;

    try
    {
        //
        // Create a new file structure here. If we exception out, we want
        // to ensure the file handle is closed.
        //

        hub::filesystem::file file(base_path.str());

        file.read_entirely(data);
    }
    catch(const hub::base::status_exception&)
    {
        //
        // Failed to read the path? May have just unlocked, or
        // maybe something else is awry. Just return for now. We
        // failed to break it.
        //

        return;
    }

    //
    // Next, let's verify we got a few bytes... If we didn't read
    // enough data, bail out.
    //

    if(data.length() <= 8)
        return;

    //
    // And now convert it to seconds.
    //

    double seconds_then = hub::base::lexical_cast<double>(data);

    //
    // If it looks like their file is too old, we will just delete it.
    //

    double delta = hub::base::wall_clock::get_as_seconds() - seconds_then;

    if(delta >= reap_timeout && reap_timeout >= 0.0)
    {
        try
        {
            //
            // Ok, we want to delete it... this is the really tricky part,
            // because somebody may have just deleted it and created their
            // own lock!!
            //

            base_path.remove_if_exists();
        }
        catch(const hub::base::status_exception&)
        {
            //
            // This is frustrating. If this fails, it is for one
            // two reasons: The file no longer exists, or somebody
            // else deleted it out from under us.
            //
            // We try to figure it out by looking to see if the file
            // still exists here. If so, then it might be permissions
            // related, and we re-throw.
            //

            if(base_path.exists() == true)
                throw;
        }

        //
        // This is the main area of contention, and I'm not sure how to
        // really fix it. What we'll do instead is delete the file, and
        // then sleep for a second or two, to allow everyone else to
        // also delete their files (hopefully...) and then we can
        // move on and try locking.
        //

        hub::base::sleep(2.0);
    }
}

/*
 * ################################################################################################
 */

void lock_file::refresh_path(bool new_lock)
{
    if (new_lock)
    {
        //Open with create_new will fail if the file already exists, meaning there is already a lock present
        base_path.open( hub::base::access_write,
                    hub::base::disposition_create_new,
                    hub::base::caching_behavior_default);
    } else
    {
        base_path.open( hub::base::access_write,
                    hub::base::disposition_create_always,
                    hub::base::caching_behavior_default);
    }
    
    //
    // Just write out the active timestamp, in string form, to avoid
    // any weird serialization code (and needing to pull that in).
    //

    hub::base::wall_timestamp time = hub::base::wall_clock::get_now();

    std::string content = hub::base::lexical_cast<std::string>(time.get_as_seconds());

    base_path.write_entirely(content);

    //
    // When we close the path (after writing the time out) we want to flush
    // it out to disk. This has a few side effects (most importantly, it fixes
    // a few bugs in NFS that could occur from multiple readers).
    //

    base_path.flush();
    base_path.close();
}

/*
 * ################################################################################################
 */

bool lock_file::is_locked() const
{
    //If the base path file exists, it is locked
    return base_path.exists();
}
