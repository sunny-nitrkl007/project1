//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/journaled_file.cc
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
///  
/// @brief A journaled file is a file object that allows you to open (or restore
/// contents in a fashion that should be safe, even in power loss.
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
///     2012-10-30    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <hub/base/status_exception.hh>
#include <hub/base/byte_buffer.hh>

#include <filesystem/journaled_file.hh>
#include <filesystem/file.hh>

#include <limits>

//
// Everything we do here is in the filesystem namespace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

journaled_file::journaled_file() : file(),
                                   access_flags(hub::base::access_read)
{
}

/*
 * ################################################################################################
 */

journaled_file::journaled_file (
                                 const path &source
                               )
                               :
                               file(source),
                               access_flags(hub::base::access_read)
{
}

/*
 * ################################################################################################
 */

journaled_file::~journaled_file()
{
    //
    // Make sure the file is committed, with our close routine, as opposed
    // to file's close routine.
    //

    if(is_file_open == true)
    {
        try
        {
            close();
        }
        catch(const hub::base::status_exception &)
        {
            //
            // We only allow exceptions to propagate here if we are not
            // already unwinding the stack. Otherwise, the system is already
            // in a bad, possibly unrecoverable state, and we don't need
            // to make things worse.
            //
            // Note that we still manually try to close the file, before
            // we crash out of here.
            //

#if __cplusplus >= 201703L
            if(std::uncaught_exceptions() > 0)
#else
            if(std::uncaught_exception() == false)
#endif
            {
                if(is_file_open == true)
                {
                    file::close();

                    is_file_open = false;
                }

                // Destructors are by default noexcept and changing this to an exception raising
                // destructor requires loosening exception requirements many other places.
                // std::terminate retains exsiting behavior, but is more explicit than
                // a throw causing immediate termination.
                std::terminate();
            }
        }
    }
}

/*
 * ################################################################################################
 */

void journaled_file::open (
                            hub::base::access_flags flags,
                            hub::base::open_disposition disposition,
                            hub::base::caching_behavior behavior
                          )
{
    //
    // If the file is already open, we are done. Throw an error.
    //

    if(is_file_open)
    {
        throw hub::base::status_exception("Tried to reopen an already open journaled file, \"%s\".", c_str());
    }

    //
    // Save the access flags off, so we know what to do
    // when the file is closed.
    //

    access_flags = flags;

    //
    // Behavior is different if we are in write mode or read mode.
    // For write mode, we always want to just open the journaled
    // file and let them modify that.
    //

    if(flags & hub::base::access_write)
    {
        //
        // Verify they aren't trying to open this file... they are
        // trying to create it.
        //

        if (
             disposition == hub::base::disposition_open_always ||
             disposition == hub::base::disposition_open_existing
           )
        {
            throw hub::base::status_exception("You cannot open an existing journaled file for writing, you "
                                                "can only create such files.");
        }

        //
        // Open the file in write mode and get out of here.
        //

        hub::filesystem::path journal_path = get_journal_path();

        hub::base::create_file(handle, journal_path.str(), flags, disposition, behavior);

        is_file_open = true;
    }
    else
    {
        //
        // Otherwise, we are just opening for read access. The real file
        // should always be present.
        //

        hub::base::create_file(handle, path::str(), flags, disposition, behavior);

        is_file_open = true;
    }
}

/*
 * ################################################################################################
 */

void journaled_file::close()
{
    //
    // Ask file to take care of closing for us.
    //
    // Notice that we explicitly flush the file here. Close, by itself,
    // may not report any errors if the disk is having trouble. Flush
    // will report those errors.
    //
    // Only flush if we have write access, so that Windows doesn't
    // complain about permissions issues.
    //

    if(access_flags & hub::base::access_write)
    {
        file::flush();
    }

    file::close();

    is_file_open = false;

    //
    // If we were opened in write mode, we need to do some extra work
    // at this point. All we do is "move" the journaled file overtop
    // the original.
    //
    // This boils down to an atomic replace operation, and allows us
    // to safely swap files out, so we never run the danger of having
    // a corrupted or partially written file on disk.
    //
    // This is the magic, because we can now safely assume that the base
    // file is *always* present, and we end up cleaning up a race
    // condition (but we still have missed a multi-writer race, but not
    // much we can do about that without locking).
    //

    if(access_flags & hub::base::access_write)
    {
        hub::filesystem::path journal_path = get_journal_path();

        hub::base::move_path(journal_path.str(), path::str());
    }
}

/*
 * ################################################################################################
 */

hub::filesystem::path journaled_file::get_journal_path() const
{
    return hub::filesystem::path(path::str() + ".hjournal");
}

/*
 * ################################################################################################
 */

bool journaled_file::operator== (
                                  const journaled_file& other
                                ) const
{
    return ((const path&) *this) == ((const path&) other);
}
