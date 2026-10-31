////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppUtil
//
// File Name: FileTransferBridgeAppUtil.cpp
//
//  Abstract: Utilities used by the Bridge application.
//            Implementation of the utilities functions.
//
////////////////////////////////////////////////////////

#include <fstream> // ifstream, ofstream
#include <sstream> // stringstream
#include <algorithm> // sort, replace
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include "FileTransferBridgeAppUtil.h"
#include "FileTransferBridgeAppLog.h"

using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::IsDirectory
// Description     : Determines if a directory exists in the file system
// Return Type     : bool - true if the provided path is a directory, otherwise false
// Argument [in]   : const std::string& path - Path in the file system
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::IsDirectory( const std::string& path )
{
   struct stat sb;
   if ( ( 0 == stat(path.c_str(), &sb) ) && ( S_ISDIR( sb.st_mode ) ) )
   {
      return true;
   }

   return false;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::GetFileAttributes
// Description     : Obtains file information from the file system:
//                      size, type, and last modification time
// Return Type     : bool - 'true' if the information was obtained successfully,
//                   'false' otherwise
// Argument [in]   : const std::string& filePath - Path to the file in the file system,
//                   const std::string& fileName - Name of the file,
//                   const unsigned long int fidSource - Functional ID of the source,
//                   const unsigned long int fidDest - Functional ID of the destination.
// Argument [out]  : FileInfo_t& fileInfo - Structure containing the information
//                   on the file
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::GetFileAttributes(const std::string& filePath,
        const std::string& fileName,
        const unsigned long int fidSource,
        const unsigned long int fidDest,
        FileInfo_t& fileInfo) {

    std::string fullPath = filePath + fileName;
    struct stat filestat;

    // Instead of calling IsDirectory, which calls 'stat', just call 'stat' once here
    // and check to see if it is a directory with one call.
    if (0 == stat(fullPath.c_str(), &filestat)) {
        if (S_ISDIR(filestat.st_mode)) {
            return false;
        }
        else {
            fileInfo.TelematicsFileNumber = GetFileType(fileName);
            fileInfo.ModifyTime = static_cast<unsigned_32>(filestat.st_mtime);
            fileInfo.SizeInBytes = filestat.st_size;
            fileInfo.DirPath = filePath;
            fileInfo.Name = fileName;
            fileInfo.SourceFID = fidSource;
            fileInfo.DestinationFID = fidDest;
            return true;
        }
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::FileExist
// Description     : Checks if the file from the provided path exists
// Return Type     : bool - 'true' if file exists, 'false' otherwise
// Argument [in]   : const std::string& fileAbsPath - Path in the file system
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::FileExist( const std::string& fileAbsPath )
{
   struct stat st;
   return ( 0 == stat( fileAbsPath.c_str(), &st ) );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::ReadFilesFromDirectory
// Description     : Reads the list of the files and their properties in a directory
// Return Type     : std::vector<FileInfo_t> - Container with the obtained files
// Argument [in]   : const std::string& dirPath - The path of the directory to read
//                   CdaFileType_t fileType - Type of files that are of interest
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
std::vector<FileInfo_t> FileTransferBridgeAppUtil::ReadFilesFromDirectory( const std::string& dirPath, CdaFileType_t fileType )
{
   struct dirent* pDirEntry;
   std::vector<FileInfo_t> files;
   DIR* pDirHandle = opendir( dirPath.c_str() );

   if ( nullptr == pDirHandle )
   {
      BRIDGE_APP_LOG("Error (" << errno << ") opening " << dirPath, AIS_LOG_ERROR, false);
      return files;
   }

   // Read files one by one
   while ( nullptr != ( pDirEntry = readdir( pDirHandle ) ) )
   {

      FileInfo_t fileInfo;
      std::string fileName(pDirEntry->d_name);

      if ( GetFileAttributes( dirPath, fileName, fileInfo.SourceFID, fileInfo.DestinationFID, fileInfo ) )
      {
         // If the type of this file matches the one that the caller is interested in, then add it to the return list
         if ( fileType == fileInfo.TelematicsFileNumber )
         {
            files.push_back( fileInfo );
         }
      }
      else if (DT_LNK == pDirEntry->d_type) {
         // Clean up the broken link
         BRIDGE_APP_LOG("Deleting broken link " << fileName, AIS_LOG_WARN, false);
         DeleteFile(dirPath + fileName);
      }
   }

   closedir( pDirHandle );

   // Sort the list of the files by the file modification time (specified in the definition of FileInfo_t by an overloaded operator)
   std::sort( files.begin(), files.end() );

   return files;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::GetFileType
// Description     : Returns the type of the file from the file name
// Return Type     : CdaFileType_t - The combined digits in file name before underscore character
// Argument [in]   : const std::string& fileName - The name of the file
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
CdaFileType_t FileTransferBridgeAppUtil::GetFileType( const std::string& fileName )
{
   std::stringstream stream( fileName );
   CdaFileType_t ret_val = 0;

   // Find the first integer in the file name and extract it
   stream >> ret_val;

   return ret_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::MakeDirFullPath
// Description     : Creates a directory even if the path doesn't exist
// Return Type     : bool - 'true' if the directory was created successfully
// Argument [in]   : const std::string& path - Path in the file system
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::MakeDirFullPath( const std::string& path )
{
   bool ret_val = false;
   const mode_t dirMode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH; // R/W/X for user, R/W/X for group, R/X for other

   if ( 0 == mkdir( path.c_str(), dirMode ) )
   {
      return true;
   }
   else
   {
      // Check for errors
      if ( ENOENT == errno )
      {
         // Parent directory does not exist. Call this function recursively until all parents are created.
         if( MakeDirFullPath( path.substr( 0, path.find_last_of('/') ) ) )
         {
            ret_val = ( 0 == mkdir( path.c_str(), dirMode ) );
         }
         else
         {
            ret_val = false;
         }
      }
      else if ( EEXIST == errno )
      {
         ret_val = true;
      }
   }

   return ret_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::PathFixSlash
// Description     : Converts DOS file path to Unix file path ("\" -> "/")
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : std::string& dirPath - The string with the path to transform
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppUtil::PathFixSlash( std::string& dirPath )
{
   std::replace( dirPath.begin(), dirPath.end(), '\\', '/' );

   // Also add a trailing slash
   if ( '/' != dirPath.back() )
   {
      dirPath.push_back( '/' );
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::DeleteFile
// Description     : Deletes the specified file
// Return Type     : bool - 'true' if deletion was successful, 'false' otherwise
// Argument [in]   : const std::string& filePath - Path in the file system
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::DeleteFile(const std::string& filePath) {
    bool returnValue = false;

    if (0 != remove(filePath.c_str())) {
        if (ENOENT == errno) {
            BRIDGE_APP_LOG("Delete file not found " << filePath, AIS_LOG_WARN, false);
            returnValue = true;
        }
        else {
            BRIDGE_APP_LOG("Delete file failed for " << filePath, AIS_LOG_ERROR, true);
        }
    }
    else {
        returnValue = true;
    }

    return returnValue;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::CreateNewFile
// Description     : Routine that creates new files in the file
//                   space defined in the config file.
// Return Type     : bool - 'true' if file created successfully, 'false' otherwise
// Argument [in]   : const FileInfo_t& fileInfo - File information, such as name and path,
//                   const std::string& fileContent - Contents of the file.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::CreateNewFile( const FileInfo_t& fileInfo, const std::string& fileContent )
{
   std::ofstream fileHandle( fileInfo.DirPath + "/" + fileInfo.Name, std::ofstream::binary );

   if( fileHandle.is_open() )
   {
      fileHandle << fileContent;
      if( fileHandle.fail() )
      {
         BRIDGE_APP_LOG( "Unable to write to " << fileInfo.Name, AIS_LOG_ERROR, true );
         return false;
      }
   }
   else
   {
      BRIDGE_APP_LOG( "Unable to create " << fileInfo.Name, AIS_LOG_ERROR, true );
      return false;
   }

   return true;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::ReadFile
// Description     : Routine that reads a file and returns its contents
// Return Type     : bool - 'true' if file read successfully, 'false' otherwise
// Argument [in]   : const FileInfo_t& fileInfo - File information, such as name and path.
// Argument [out]  : std::string& fileContents - Storage for the contents of the file.
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppUtil::ReadFile( const FileInfo_t& fileInfo, std::string& fileContents )
{
   std::string fullFilePath = fileInfo.DirPath + "/" + fileInfo.Name;
   std::ifstream fileHandle( fullFilePath, std::ifstream::binary );

   if( fileHandle.is_open() )
   {
      std::stringstream sstr;
      while ( fileHandle >> sstr.rdbuf() )
      {
         if( fileHandle.fail() )
         {
            BRIDGE_APP_LOG( "Unable to read from " << fullFilePath, AIS_LOG_ERROR, true );
            return false;
         }
      }

      fileContents = sstr.str();
   }
   else
   {
      BRIDGE_APP_LOG( "Unable to open " << fullFilePath, AIS_LOG_ERROR, true );
      return false;
   }

   return true;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::GetTimeNow
// Description     : Returns a current time reference
// Return Type     : time_point - Time reference
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
std::chrono::system_clock::time_point FileTransferBridgeAppUtil::GetTimeNow( void )
{
   return std::chrono::system_clock::now();
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds
// Description     : Returns the difference in time between now and the
//                   provided time reference
// Return Type     : int_32 - Time difference in milliseconds
// Argument [in]   : const system_clock::time_point& timeReference - Time reference
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
int_32 FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds( const std::chrono::system_clock::time_point& timeReference )
{
   auto timeNow = GetTimeNow();
   auto timeSince = timeNow - timeReference;
   auto timeSinceMs = std::chrono::duration_cast<std::chrono::milliseconds>( timeSince );

   return timeSinceMs.count();
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppUtil::CleanDirectory
// Description     : Wipes out all the files in the specified directory
// Return Type     : None
// Argument [in]   : const std::string& dirPath - Directory path
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppUtil::CleanDirectory( const std::string& dirPath )
{
   struct dirent* pDirEntry;
   DIR* pDirHandle = opendir( dirPath.c_str() );

   if ( nullptr == pDirHandle )
   {
      BRIDGE_APP_LOG("Error (" << errno << ") opening " << dirPath, AIS_LOG_ERROR, false);
   }

   // Read files one by one
   while ( nullptr != ( pDirEntry = readdir( pDirHandle ) ) )
   {
      std::string fullPath = dirPath + pDirEntry->d_name;
      if ( !IsDirectory( fullPath ) && ( 0 != remove( fullPath.c_str() ) ) )
      {
         BRIDGE_APP_LOG( "Delete file failed for " << fullPath, AIS_LOG_ERROR, true );
      }
   }

   closedir( pDirHandle );
}
