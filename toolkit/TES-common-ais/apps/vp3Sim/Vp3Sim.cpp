
#include "Vp3Sim.h"
#include <sys/stat.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace task;

std::ofstream fileWriter;
AppReg regInfo;

AbstractTaskCore* task::getTaskImplementation(void)
{
   static Vp3Sim thisTask("Vp3Sim");
   return dynamic_cast<Task *>(&thisTask);
}

Vp3Sim::Vp3Sim( const std::string& taskName ):
                      Task( taskName ),
                      FileTransferBridgeResponseInput_( NULL ),
                      FileTransferBridgeRequestOutput_( NULL ),
                      m_FileCountTarget( 0 ),
                      m_FileCountCurrent( 0 ),
                      m_FileSize( 5 ),
                      m_RunSftTest( false )
{
}

Vp3Sim::~Vp3Sim( )
{
}

bool Vp3Sim::initialize( )
{
   AIS_LOG_NOTICE( "Vp3Sim::initialize" );

   FileTransferBridgeResponseInput_ = dynamic_cast<FileTransferBridgeResponseInput*>( InterfaceDb::fetch( "FileTransferBridgeResponseInput" ) );
   FileTransferBridgeRequestOutput_ = dynamic_cast<FileTransferBridgeRequestOutput*>( InterfaceDb::fetch("FileTransferBridgeRequestOutput") );

   if (FileTransferBridgeResponseInput_)
   {
      FileTransferBridgeResponseInput_->addNewDataSlot( boost::bind( &Vp3Sim::Vp3SimSendFileAttrRespRead, this ) );
   } else {
      AIS_LOG_ERROR( "no FileTransferBridgeResponseInput_ interface defined" );
      return false;
   }

   if ( !FileTransferBridgeRequestOutput_ )
   {
      AIS_LOG_ERROR( "no FileTransferBridgeRequestOutput_ interface defined" );
      return false;
   }

   AIS_LOG_NOTICE("Send vp3app reg to bridge app.");
   regInfo.SetAppRegAttr("Vp3App", AppRegStorage::APP_REG_STATE_ACTIVE, "FileTransferBridgeApp");

   if(getTaskConfig().get("DataFileStorePath", m_DefaultDataFilePath))
   {
      AIS_LOG_NOTICE("DefaultDataFilePath: %s", m_DefaultDataFilePath.c_str());
   }
   else
   {
      AIS_LOG_ERROR("Failed to read DefaultDataFilePath: %s", m_DefaultDataFilePath.c_str());
      return false;
   }

   (void)getTaskConfig().get("fileCount", m_FileCountTarget);
   (void)getTaskConfig().get("fileSize", m_FileSize);
   (void)getTaskConfig().get("runSftTest", m_RunSftTest);
   (void)getTaskConfig().get("fileTypes", m_FileTypes);

   //check directory exists
   if(!IsDirectory(m_DefaultDataFilePath.c_str()))
   {
      MakeDirFullPath(m_DefaultDataFilePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   }
   m_FileCountCurrent = 0;
   return true;
}

void Vp3Sim::Vp3SimSendFileAttr( unsigned_32 FileNumber )
{
   FileTransferBridgeRequest type;
   type.fileAttr.TelematicsFileNumber = FileNumber;
   type.GenerateFileNamev2(type.fileAttr.TelematicsFileNumber, "CAT00000");
   type.fileAttr.DirPath = m_DefaultDataFilePath;
   string newFilePath = (m_DefaultDataFilePath + type.fileAttr.Name);
   CreateFile(newFilePath.c_str(),m_FileSize);
   type.fileAttr.SizeInBytes = m_FileSize;
   if( m_RunSftTest )
   {
      type.fileAttr.FidDestination = 0x00520000;
      type.fileAttr.FidSource = 0x00580000;
   }
   AIS_LOG_NOTICE("Generated file: %s", newFilePath.c_str());
   FileTransferBridgeRequestOutput_->publish( type );
}

void Vp3Sim::Vp3SimSendFileAttrRespRead( )
{
   //LOG_NOTICE( "task configured to read from input interface" );
   FileTransferBridgeResponse type;
   while ( FileTransferBridgeResponseInput_->get(type) )
   {
      AIS_LOG_NOTICE("FileTransferBridgeResponseInput_ %d ", type.Response.Ret );
      AIS_LOG_NOTICE("FileTransferBridgeResponseInput_ %s ", type.Response.Msg.c_str() );
      AIS_LOG_NOTICE("FileTransferBridgeResponseInput_ %s ", type.Response.FileName.c_str() );
   }
}

bool Vp3Sim::executive( )
{
   if ( m_FileCountCurrent++ < m_FileCountTarget )
   {
      for ( auto& fileType : m_FileTypes )
      {
         Vp3SimSendFileAttr( fileType );
      }
   }         AIS_LOG_ERROR( "dsfv");

   return true;
}

// Tests
// 1. task with an executive thread at 100Hz, determine if timing is periodic as expected (.01s between cycles)
// 2. task with 100Hz thread, receiving from 3 interfaces, data published at 1Hz, 20Hz, 100Hz
// 3. publishing data from both callback methods and from executive method
// 4. interfaces with 1 and 10 deep queues
// 5. reading 1 at a time, versus draining queue in callback
// 6. reading data in executive versus in a callback



void Vp3Sim::cleanup( )
{
   AIS_LOG_NOTICE( "Vp3Sim::cleanup" );

   regInfo.SetAppRegAttr("Vp3App", AppRegStorage::APP_REG_STATE_INACTIVE, "FileTransferBridgeApp");
}

bool Vp3Sim::IsDirectory( const char *path )
{
   struct stat sb;

   if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
   {
      return true;
   }

   return false;
}

void Vp3Sim::CreateFile(const char* fileName, unsigned_32 size)
{
   string command= "head -c " + std::to_string(size) +  " /dev/urandom > " + fileName;
   std::system(command.c_str());
}

Ret_t Vp3Sim::MakeDirFullPath(const char *path, mode_t mode)
{
   const size_t len = strlen(path);
   char pathMax[PATH_MAX];
   char *p;

   errno = 0;

   /* Copy string so its mutable */
   if (len > sizeof(pathMax)-1)
   {
      errno = ENAMETOOLONG;
      return (RET_ERROR);
   }
   strcpy(pathMax, path);

   /* Iterate the string */
   for (p = pathMax + 1; *p; p++)
   {
      if (*p == '/') {
         /* Temporarily truncate */
         *p = '\0';

         if (mkdir(pathMax, mode) != 0 && errno != EEXIST)
         {
            return (RET_ERROR);
         }

         *p = '/';
      }
   }

   if (mkdir(pathMax, mode) != 0 && errno != EEXIST)
   {
      return (RET_ERROR);
   }

   return (RET_SUCCESS);
}
