/**********************************************************************************
Copyright 2013 Caterpillar Inc.  All rights reserved.
-----------------------------------------------------------------------------------

Filename:   fsa.h
Language:   C89

Summary
This file contains the public interface to the File System Abstraction library.
***********************************************************************************/

#ifndef FSA_H
#define FSA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <std_t.h>

/***********************************************************************************************************************
Function name:
   fsa_get_available_space

Description:
   Gets the amount of free space on a mounted file system.

Parameter Description:
   int_least64_t *space_available = returned space on file system (in bytes)
   const char *directory_path = file system to get available space

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
**********************************************************************************************************************/
int_least32_t fsa_available_space
(
   uint_least64_t *space_available,
   const char *directory_path
);

/***********************************************************************************************************************
Function name:
   fsa_clean_directory

Description:
   Deletes all files and subdirectories within a directory, provided directoy argument is also deleted.
   Esentially "rm -rf <directory_path>"

Parameter Description:
   const char *directory_path = path to directory to clean

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_clean_directory
(
   const char *directory_path
);

/***********************************************************************************************************************
Function name:
   fsa_copy_file

Description:
   Copies a file to the specified destination.  If a file already exists at the destination, it is deleted.

Parameter Description:
   const char *source_file_path = path to file to be copied
   const char *destination_file_path = new path for file

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_copy_file
(
   const char *source_file_path,
   const char *destination_file_path
);

/***********************************************************************************************************************
Function name:
   fsa_delete_directory

Description:
   Deletes the specified directory.

Parameter Description:
   const char *directory_path = path to directory to delete

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_delete_directory
(
   const char *directory_path
);

/***********************************************************************************************************************
Function name:
   fsa_delete_file

Description:
   Deletes the specified file (including symbolic links and hard links).
   Will not delete a directory.

Parameter Description:
   const char *file_path = path to file to delete

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_delete_file
(
   const char *file_path
);

/***********************************************************************************************************************
Function name:
   fsa_get_file_size

Description:
   Gets the size (in bytes) of the specified file.

Parameter Description:
   const char *file_path = path to file
   uint_least64_t *file_size = pointer to size of file

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_get_file_size
(
   const char *file_path,
   uint_least64_t *file_size
);

/***********************************************************************************************************************
Function name:
   fsa_make_directory

Description:
   Create a directory or directory tree.

Parameter Description:
   const char *directory_path = directory or directory tree to create

Return Description:
   Returns 0 if successful, an -1 if unsuccessful and errno is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_make_directory
(
   const char *directory_path
);

#if !defined(_WIN32) && !defined(_WIN32_WCE) /* Not supported in Windows */

/***********************************************************************************************************************
Function name:
   fsa_sync

Description:
   Compares a persistent file with a temporary file for changes.  If the files differ, the temporary file will replace
   the persistent file.

Parameter Description:
   const char *temp_file_path = path to temporary (new) file
   const char *persistent_file_path = path to persistent (original) file

Return Description:
   Returns 0 if the persistent and temporary file are the same (no action is taken), 1 if the persistent and temporary
   file are different (temporary file replaces persistent file), or -1 if function fails and errno is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_sync
(
   const char *temp_file_path,
   const char *persistent_file_path
);

/***********************************************************************************************************************
Function name:
   fsa_make_hard_link

Description:
   Creates a new link (also known as a hard link) to an existing file.
   Hard link has same inode as source.

Parameter Description:
   const char *source_file_path = path to source file
   const char *hard_link_path = path for hard link to existing file 'source_path'

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_make_hard_link
(
   const char *source_file_path,
   const char *hard_link_path
);

/***********************************************************************************************************************
Function name:
   fsa_make_symbolic_link

Description:
   Creates a symbolic link to a file or directory (existant or not).
   Symbolic link has different inode than source.

Parameter Description:
   const char *source_path = path to source file or directory
   const char *symbolic_link_path = path for symbolic link to file or directory 'source_path'

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_make_symbolic_link
(
   const char *source_path,
   const char *symbolic_link_path
);

/***********************************************************************************************************************
Function name:
   fsa_file_exists

Description:
   Checks to see if the file exists.

Parameter Description:
   const char *file_path = path to file

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_file_exists(const char *file_path);

/***********************************************************************************************************************
Function name:
   fsa_touch

Description:
   Touches a file, updating the access and modification time to current time.  If file doesn't exists, it is created.

Parameter Description:
   const char *file_path = path to file to touch

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_touch(const char *file_path);

#endif /* Not supported in Windows */

/***********************************************************************************************************************
Function name:
   fsa_lock_file

Description:
   Locks the specified file by setting all permissions to Read Only.
   Lock is "advisory". (can be ignored)

Parameter Description:
   const char *file_path = path to file to test if it exists

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_lock_file
(
   const char *file_path
);

/***********************************************************************************************************************
Function name:
   fsa_move_file

Description:
   Moves a file to the specified destination.  If a file already exists at the destination, it is deleted.
   Source file is deleted after successful move.

Parameter Description:
   const char *source_file_path = path to file to move
   const char *destination_file_path = new path for file

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_move_file
(
   const char *source_file_path,
   const char *destination_file_path
);

/***********************************************************************************************************************
Function name:
   fsa_rename_file

Description:
   Renames a file, moving it between directories if required.Hard link , open file descriptor
   to the old path are unaffected.If new path already exists it will be atomically replaced.


Parameter Description:
   const char *old_path = old path to file
   const char *new_path = new path to file

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_rename_file
(
   const char *old_path,
   const char *new_path
);

/***********************************************************************************************************************
Function name:
   fsa_unlock_file

Description:
   Unlocks the specified file.

Parameter Description:
   const char *file_path = path to file to unlock

Return Description:
   Returns 0 if successful, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
***********************************************************************************************************************/
int_least32_t fsa_unlock_file
(
   const char *file_path
);

/***********************************************************************************************************************
Function name:
   fsa_check_mountpoint

Description:
   Check if the the given file or path is a mount point or not.

Parameter Description:
   const char *mnt_path = path to file to check for mount point.

Return Description:
   Returns 0 if a mountpoint, 1 if not a mount point, -1 if unsuccessful and 'errno' is set.
   Function caller is responsible for checking 'errno' when an error is returned.
**********************************************************************************************************************/
int_least32_t fsa_check_mountpoint
(
   const char *mnt_path
);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FSA_H */
