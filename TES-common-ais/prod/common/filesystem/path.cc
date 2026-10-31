//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/path.cc
/// @ingroup hub_filesystem
/// @copyright Copyright 2012
///  
/// @brief This class manages paths. It allows you to construct child paths,
/// checks for their existence, and to manipulate them.
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
///    2012-10-28    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <hub/base/status_exception.hh>

#include <filesystem/path.hh>

#include <hub/utility/string.hh>

#include <list>

//
// Everything we do here is in the filesystem namespace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

path::path() : source_path("")
{
}

/*
 * ################################################################################################
 */

path::path (
             const path &other
           ) = default;

/*
 * ################################################################################################
 */

path::path (
             const std::string &source
           )
           :
           source_path(normalize_path(source))
{
}

/*
 * ################################################################################################
 */

path::path (
             const char *source
           )
           :
           source_path(normalize_path(source))
{
}

/*
 * ################################################################################################
 */

path::path (
             const path &parent,
             const path &child
           )
{
    //
    // If the parent is not empty, then try to merge these two
    // paths into a properly deliminated (path separated) path. Otherwise,
    // the path is really just equal to the child.
    //

    if(parent.empty() == false && child.empty() == false)
    {
        source_path = normalize_path(parent.str() + "/" + child.str());
    }
    else if(child.empty() == false)
    {
        source_path = normalize_path(child.str());
    }
    else
    {
        source_path = normalize_path(parent.str());
    }
}

/*
 * ################################################################################################
 */

path& path::operator= (
                        const path &other
                      )
{
    source_path = other.source_path;

    return *this;
}

/*
 * ################################################################################################
 */

bool path::operator< (
                       const path &other
                     ) const
{
    return (source_path < other.source_path);
}

/*
 * ################################################################################################
 */

bool path::operator> (
                       const path &other
                     ) const
{
    return (source_path > other.source_path);
}

/*
 * ################################################################################################
 */

bool path::operator== (
                        const path &other
                      ) const
{
    return (source_path == other.source_path);
}

/*
 * ################################################################################################
 */

bool path::operator!= (
                        const path &other
                      ) const
{
    return (source_path != other.source_path);
}

/*
 * ################################################################################################
 */

path path::operator/ (
                       const path &other
                     ) const
{
    return normalize_path(source_path + "/" + other.source_path);
}

/*
 * ################################################################################################
 */
std::ostream& hub::filesystem::operator<< (
                                            std::ostream &out,
                                            const path &other
                                          )
{
    out << other.str();

    return out;
}

/*
 * ################################################################################################
 */

uint64_t path::get_size() const
{
    hub::base::path_status status;

    hub::base::get_path_status(status, source_path);

    return status.size;
}

/*
 * ################################################################################################
 */

bool path::exists() const
{
    //
    // Quick check: If the path is an empty string, then
    // we do not exist.
    //

    if(source_path.length() == 0)
        return false;

    //
    // Otherwise, test for existence by getting the path
    // status. If that is possible, then we must exist.
    //

    try
    {
        hub::base::path_status status;

        hub::base::get_path_status(status, source_path);

        return true;
    }
    catch(hub::base::status_exception&)
    {
        return false;
    }
}

/*
 * ################################################################################################
 */

hub::base::path_status path::get_status() const
{
    hub::base::path_status status;

    hub::base::get_path_status(status, source_path);

    return status;
}

/*
 * ################################################################################################
 */

bool path::is_directory() const
{
    return (get_status().type == hub::base::path_directory);
}

/*
 * ################################################################################################
 */

bool path::is_regular_file() const
{
    return (get_status().type == hub::base::path_file);
}

/*
 * ################################################################################################
 */

bool path::is_absolute_path() const
{
    //
    // If the path is empty, it is obviously not absolute.
    //

    if(source_path.empty() == true)
    {
        return false;
    }

    //
    // Normalize the path first, so we know what we are operating with.
    //

    std::string normalized = normalize_path(source_path);

    //
    // If they specified the root folder, then we are absolute (this is true
    // on Windows or Linux, even though on Windows this just means the absolute
    // path within the local drive.
    //

    if(normalized[0] == '/')
    {
        return true;
    }

    //
    // If the path starts with some double backslashes, then we are an absolute.
    //

    if(hub::utility::does_string_start_with(normalized, "\\\\") == true)
    {
        return true;
    }

    //
    // On Windows only, we check to see if they have a drive path. This is a valid
    // path on pretty much every other platform.
    //

#ifdef _WIN32

    if(normalized[1] == ':' && normalized[2] == '/')
    {
        return true;
    }

#endif

    //
    // Not an (apparent) absolute path.
    //

    return false;
}

/*
 * ################################################################################################
 */

path path::get_absolute_path() const
{
    return path(hub::base::get_absolute_path(source_path));
}

/*
 * ################################################################################################
 */

path path::get_absolute_path_if_exists() const
{
    try
    {
        return get_absolute_path();
    }
    catch(const hub::base::status_exception&)
    {
        //
        // In this case, the path doesn't appear to exist. Return ourself;
        // they will just have to deal with this being an incomplete path.
        //

        return *this;
    }
}

/*
 * ################################################################################################
 */

path path::get_relative_path_from_path (
                                         const path &other
                                       ) const
{
    //
    // You cannot currently take relative paths to other relative paths.
    //

    if(source_path.find("..") != std::string::npos || other.source_path.find("..") != std::string::npos)
    {
        throw hub::base::status_exception("You cannot currently find paths relative to other relative paths. "
                                          "Consider resolving the paths with get_absolute_path() or resolve_path() "
                                          "before calling this API. The paths were \"%s\" and \"%s\".",
                                          source_path.c_str(), other.source_path.c_str());
    }

    //
    // Find a common prefix between the two paths. We can't do this
    // in string-based form, we have to do this as path components...
    // ie, they have to be separated by slashes.
    //

    std::vector<std::string> local_separated_source = hub::utility::split_string(source_path, "/");
    std::vector<std::string> other_separated_source = hub::utility::split_string(other.source_path, "/");

    size_t index = 0;

    for(; index < local_separated_source.size() && index < other_separated_source.size(); ++index)
    {
        if(local_separated_source[index] != other_separated_source[index])
            break;
    }

    //
    // We need to re-assemble the common prefix here. Make sure the first component
    // is the root folder, if it looks like we started out that way (an empty first
    // component).
    //

    hub::filesystem::path prefix;

    for(size_t sub_index = 0; sub_index < index; ++sub_index)
    {
        if(sub_index == 0 && local_separated_source[sub_index].empty() == true)
        {
            prefix = "/";
        }
        else
        {
            prefix = hub::filesystem::path(prefix, local_separated_source[sub_index]);
        }
    }

    //
    // Assume that if the prefix string is not empty, then it must end with a /.
    // This way, we strip out the full parent folder path (including leading slash).
    //

    std::string prefix_string = prefix.str();

    if(prefix_string.empty() == false && hub::utility::does_string_end_with(prefix_string, "/") == false)
        prefix_string += "/";

    //
    // Strip the prefix string off the front of both the local path
    // and the target path. If the prefix string is longer than either,
    // then leave that path totally empty.
    //

    std::string::size_type prefix_length = prefix_string.length();

    hub::filesystem::path local_path;
    hub::filesystem::path target_path;

    if(source_path.length() >= prefix_length)
        local_path = source_path.substr(prefix_length);

    if(other.source_path.length() >= prefix_length)
        target_path = other.source_path.substr(prefix_length);

    //
    // Walk through the target path and build up a new path, filled
    // with '..'s, until we hit the end.
    //

    std::string relative_path = "";

    while(target_path.empty() == false)
    {
        relative_path += "../";

        target_path = target_path.get_parent_path();
    }

    //
    // Form the final local path here.
    //

    return path(relative_path, local_path);
}

/*
 * ################################################################################################
 */

path path::get_parent_path() const
{
    //
    // Find the last slash in the string.
    //

    std::string::size_type location = source_path.find_last_of("/");

    if(location == std::string::npos)
        return path("");

    //
    // Return a substring, up to the last slash.
    //

    return path(source_path.substr(0, location));
}

/*
 * ################################################################################################
 */

path path::get_name() const
{
    //
    // Find the last slash in the string.
    //

    std::string::size_type location = source_path.find_last_of("/");

    //
    // If there are no slashes, then the name of this path is the entire
    // path itself.
    //

    if(location == std::string::npos)
        return source_path;

    //
    // Return a substring, from the last slash.
    //

    return source_path.substr(location + 1);
}

/*
 * ################################################################################################
 */

std::string path::get_name_without_extension() const
{
    //
    // Find just the filename, so we don't count periods elsewhere in the path.
    //

    std::string name = get_name().str();

    //
    // Walk backwards until we find a period.
    //

    std::string::size_type position = name.rfind('.');

    //
    // If we couldn't find one, just return the complete name.
    //

    if(position == std::string::npos)
        return name;

    //
    // Otherwise, return the substring.
    //

    return name.substr(0, position);
}

/*
 * ################################################################################################
 */

std::string path::get_extension() const
{
    //
    // Find just the filename, so we don't count periods elsewhere in the path.
    //

    std::string name = get_name().str();

    //
    // Walk backwards until we find a period.
    //

    std::string::size_type position = name.rfind('.');

    if(position == std::string::npos)
        return "";
    else
        return name.substr(position + 1);
}

/*
 * ################################################################################################
 */

void path::touch() const
{
    //
    // Open the file, and never fail. If it already exists, don't overwrite it with
    // zeroes, just "touch" it so its modification time changes.
    //

    hub::base::touch_file(source_path);
}

/*
 * ################################################################################################
 */

void path::change_owner (
                          const std::string &username
                        ) const
{
    hub::base::change_path_owner(source_path, username);
}

/*
 * ################################################################################################
 */

void path::move (
                  const hub::filesystem::path &target
                ) const
{
    hub::base::move_path(source_path.c_str(), target.source_path.c_str());
}

/*
 * ################################################################################################
 */

void path::remove() const
{
    //
    // We have different APIs if this is a directory or a file, so we need
    // to properly check before hand what type it is, before we delete the
    // file.
    //

    hub::base::path_status status = get_status();

    if(status.type == hub::base::path_directory)
    {
        //
        // Is a directory. This is the only type that needs such an explicit call.
        //

        hub::base::delete_directory(path::str());
    }
    else
    {
        //
        // All other types, we can simply delete as usual.
        //

        hub::base::delete_file(path::str());
    }
}

/*
 * ################################################################################################
 */

void path::remove_if_exists() const
{
    //
    // This way, if we can't delete it because of a permissions error,
    // we still exception out.
    //

    if(exists())
    {
        remove();
    }
}

/*
 * ################################################################################################
 */

void path::remove_recursively(bool self_remove_dir) const
{
    //
    // Don't try anything if we are already gone.
    //

    if(exists() == false)
        return;

    //
    // Let's see what kind of path we have. If we are a file,
    // just remove it and be done.
    //

    hub::base::path_status status;

    hub::base::get_path_status(status, path::str());

    if(status.type != hub::base::path_directory)
    {
        remove();
        return;
    }

    //
    // We are a directory. Let's enumerate all of the files contained
    // within us, and delete them all, in turn.
    //

    hub::base::file_iterator_handle iterator;

    hub::base::create_file_iterator(iterator, path::str());

    for(;;)
    {
        hub::base::directory_entry entry;

        if(!hub::base::continue_file_iteration(iterator, entry))
            break;

        //
        // Form a new file object, and delete that.
        //

        try
        {
            path child_path(*this / entry.name);

            child_path.remove_recursively();
        }
        catch(const hub::base::status_exception&)
        {
            //
            // An error occurred. Clean up before we throw it
            // out of this routine!
            //

            hub::base::destroy_file_iterator(iterator);
            throw;
        }
    }

    //
    // All done. Clean up and remove ourself.
    //

    hub::base::destroy_file_iterator(iterator);

    if (self_remove_dir)
    {
        remove();
    }
}

/*
 * ################################################################################################
 */

void path::make_directories() const
{
    //
    // Fast path -- check to see if this path already exists. If so,
    // we can skip quite a bit of work. We don't do this before each
    // of the mkdirs() below, because each call to stat() is just as
    // bad as a call to mkdir()!
    //

    if(exists() == true)
    {
        return;
    }

    //
    // Walk through the string and look for slash characters. This
    // is assuming the path is already normalized.
    //

    std::list<std::string> elements;

    hub::utility::split_string(elements, path::str(), "/");

    //
    // We actually only want every entry *but* the last one.
    //

    std::list<std::string>::const_iterator iterator = elements.begin();

    std::string total_path;

    while(iterator != elements.end())
    {
        //
        // Get the sub path element out.
        //

        const char *sub_path = iterator->c_str();

        //
        // Have a directory. Let's make it. But we need to keep
        // appending, so we have a complete path. Note that we watch
        // for empty strings, to catch the root folder specified case.
        //

        if(sub_path[0])
        {
            total_path += sub_path;

            hub::base::make_directory(total_path);
        }

        total_path += "/";

        //
        // Advance the iterator. If'we done, we can get out of this
        // routine, we've created all of the necessary directories.
        //

        ++iterator;
    }
}

/*
 * ################################################################################################
 */

void path::make_parent_directories() const
{
    //
    // We'll just construct a new file object, based off of our parent
    // directory, and then create directories normally off of that. This
    // is slight more inefficient then just calling make_directories() with
    // their iterator adjusted, but if you are making directories, it
    // probably doesn't matter.
    //

    get_parent_path().make_directories();
}

/*
 * ################################################################################################
 */

directory_entry_list path::enumerate_children() const
{
    directory_entry_list list;

    //
    // We'll need the platform abstraction layer for this.
    //

    hub::base::file_iterator_handle iterator;

    hub::base::create_file_iterator(iterator, source_path);

    try
    {
        //
        // Iterate until we run out of files, appending them all to
        // the end of a list.
        //

        for(;;)
        {
            hub::base::directory_entry entry;

            if(!hub::base::continue_file_iteration(iterator, entry))
                break;

            list.push_back(entry);
        }
    }
    catch(const hub::base::status_exception&)
    {
        //
        // We had an error. We need to clean up the file iterator, and then rethrow.
        //

        hub::base::destroy_file_iterator(iterator);

        throw;
    }

    //
    // All done. Clean up and return the final list.
    //

    hub::base::destroy_file_iterator(iterator);

    return list;
}

/*
 * ################################################################################################
 */

bool path::change_permissions(std::string desired_permissions) const
{
    struct stat statbuf;
    if (stat(source_path.c_str(), &statbuf) != 0) {
         return false;
    } else {
        std::stringstream logPerm("");
        logPerm << std::oct << (statbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

        if (logPerm.str() != desired_permissions) {
            std::stringstream command_str("");
            command_str << "chmod " << desired_permissions << " -R \"" << source_path << '\"';

            if (system(command_str.str().c_str()) != 0) {
                return false;
            }
        }
    }
    return true;
}

/*
 * ################################################################################################
 */

bool path::empty() const
{
    return source_path.empty();
}

/*
 * ################################################################################################
 */

const std::string& path::str() const
{
    return source_path;
}

/*
 * ################################################################################################
 */

const char* path::c_str() const
{
    return source_path.c_str();
}

/*
 * ################################################################################################
 */

std::string path::normalize_path (
                                   const std::string &raw_path
                                 ) const
{
    //
    // If the path starts with a double backslash, then it is most likely a
    // Windows CIFS path. Remember that that happenned -- we are going to
    // reconvert things later on to make it acceptable.
    //

    bool is_windows_cifs_path = hub::utility::does_string_start_with(raw_path, "\\\\");

    //
    // Replace all backslashes with forward slashes.
    //

    std::string final_string = hub::utility::replace_characters_copy(raw_path, '\\', '/');

    //
    // Search for each instance of double slashes. Notice that this is *slightly*
    // different than just a find & replace, in that we want to make sure we have
    // no instances of double slashes anywhere in the string -- whereas find & replace
    // could still drop down to two in a row (if you have //// for example).
    //

    for(;;)
    {
        std::string::size_type location = final_string.find("//");

        if(location == std::string::npos)
            break;

        final_string.replace(location, 2, "/");
    }

    //
    // Let's remove any trailing slashes.
    //

    for(;;)
    {
        //
        // Check to see if the string is empty, or if the last character is not
        // a slash. If so, we can break out and be done.
        //

        std::string::size_type length = final_string.length();

        if(length <= 1 || final_string[length - 1] != '/')
            break;

        //
        // Nope, the last character is a slash. Remove it.
        //

        final_string = final_string.substr(0, length - 1);
    }

    //
    // Finally, if we were a Windows CIFS path, then we remove the first
    // slash at the start of the path, and convert it back into a series of
    // backslashes, for Windows.
    //

    if(is_windows_cifs_path)
    {
        std::string::size_type length = final_string.length();

        final_string = "\\\\" + final_string.substr(1, length - 1);

        //
        // In addition to this, the very first path element needs to be converted
        // into a backslash as well, for Windows.
        //

        std::string::size_type location = final_string.find("/");

        if(location != std::string::npos)
            final_string.replace(location, 1, "\\");
    }

    //
    // Return the final result.
    //

    return final_string;
}

/*
 * ################################################################################################
 */

path path::resolve_path() const
{
    //
    // The algorithm here will basically do the following:
    //   - Search for the first slash present
    //   - If the contents of that path component are ., ignore
    //   - If the contents of that path components are .., remove previous component
    //   - Otherwise, copy it on the stack
    //

    std::vector<std::string> source_components = hub::utility::split_string(source_path, "/");

    std::vector<std::string> destination_components;

    hub_const_iterate_over(iterator, source_components, std::vector<std::string>)
    {
        const std::string &component = *iterator;

        //
        // If the component is totally empty, then it is a slash. We are
        // normalized, so this should be safe. Still, make sure we think
        // we are at the first node. This is all because split string will
        // consider the first path to be empty.
        //

        if(iterator == source_components.begin() && component.length() == 0)
        {
            destination_components.push_back("/");
            continue;
        }

        //
        // If the component is just a dot, ignore it.
        //

        if(component == ".")
            continue;

        //
        // If the component is two dots, than we pop the top element off
        // the destination components.
        //

        if(component == "..")
        {
            //
            // If the destination components array is empty, we have an exception
            // condition. This would be like ("abc/../../def") -- we can't do it.
            //

            if(destination_components.empty() == true)
            {
                throw hub::base::status_exception("The path \"%s\" could not be resolved. The path does not contain "
                                                    "enough components to be fully resolved.", source_path.c_str());
            }

            //
            // ... unless we are at a root level, then we ignore the extra ..
            // requests.
            //

            if(destination_components.size() == 1)
            {
                const std::string &first_component = destination_components[0];

                //
                // For Unix, the root path (/) is the only one we care about.
                //

                if(first_component == "/")
                    continue;

#ifdef _WIN32
                //
                // For Windows, we ignore CIFS paths (\\somepath) and also
                // drive letter paths.
                //

                if(first_component == "\\\\")
                    continue;

                if(first_component[1] == ':' && first_component[2] == '/')
                    continue;

#endif
            }

            //
            // If we got here, we can pop that component off the chain.
            //

            destination_components.pop_back();
            continue;
        }

        //
        // Whew. At this point we have a normal component. Just append it to
        // the list.
        //

        destination_components.push_back(component);
    }

    //
    // Join the entire string together, and then return the normalized result.
    //

    std::string joined_path = hub::utility::join_strings(destination_components, "/");

    return normalize_path(joined_path);
}

/*
 * ################################################################################################
 */

export_object path_list hub::filesystem::split_path_list (
                                                           const std::string &path_list
                                                         )
{
    //
    // Ask the utility library to split these up for us.
    //

    std::list<std::string> split_paths;

    hub::utility::split_string(split_paths, path_list, ":;");

    //
    // Now transform them into a list of paths.
    //

    hub::filesystem::path_list returned_paths;

    hub_const_iterate_over(iterator, split_paths, std::list<std::string>)
    {
        const std::string &split_path = *iterator;

        returned_paths.push_back(split_path);
    }

    //
    // Return the final result.
    //

    return returned_paths;
}
