////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppUtil
//
// File Name: FileTransferBridgeAppUtil.h
//
//  Abstract: Utilities used by the Bridge application.
//            Definition of the utilities functions.
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGEUTIL_H
#define SCSCDATTIBRIDGEUTIL_H

#include <string> // std::string
#include <vector> // std::vector
#include <chrono> // std::chrono
#include <unistd.h>
#include <cat_std_types.h>

#include "FileTransferBridgeAppDef.h"

class FileTransferBridgeAppUtil
{
public:
   //File
   static bool GetFileAttributes ( const std::string& filePath,
         const std::string& fileName,
         const unsigned long int fidSource,
         const unsigned long int fidDest,
         FileTransferBridge::FileInfo_t& fileInfo );
   static FileTransferBridge::CdaFileType_t GetFileType( const std::string& fileName );
   static bool GetFileLastModTime( const std::string& fileAbsPath, struct timespec& mtime );
   static bool DeleteFile( const std::string& filePath );
   static bool FileExist( const std::string& fileAbsPath );
   static bool CreateNewFile( const FileTransferBridge::FileInfo_t& fileInfo, const std::string& fileContent );
   static bool ReadFile( const FileTransferBridge::FileInfo_t& fileInfo, std::string& fileContents );

   //Directory
   static bool IsDirectory( const std::string& path );
   static std::vector<FileTransferBridge::FileInfo_t> ReadFilesFromDirectory( const std::string& dirPath, FileTransferBridge::CdaFileType_t fileType );
   static bool MakeDirFullPath( const std::string& path );
   static void CleanDirectory( const std::string& dirPath );

   //Other
   static void PathFixSlash( std::string& DirPath );
   static std::chrono::system_clock::time_point GetTimeNow( void );
   static int_32 GetTimeSinceInMilliseconds( const std::chrono::system_clock::time_point& timeReference );
   inline static bool IsSFTNode( const FileTransferBridge::CdaNode_t& node ) { return node > 0xFF; }

private:
   FileTransferBridgeAppUtil( ) { }
   ~FileTransferBridgeAppUtil( ) { }
};

#endif // SCSCDATTIBRIDGEUTIL_H
