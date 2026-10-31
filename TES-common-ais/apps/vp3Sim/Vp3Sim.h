#ifndef VP3SIM_H
#define VP3SIM_H

#include <ais/task/Task.h>

#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeResponse/InterfaceTypes.h>
#include <interfaces/AppReg/InterfaceTypes.h>
#include <std_types.h>

typedef enum
{
   RET_SUCCESS = 0,
   RET_ERROR
}Ret_t;


class Vp3Sim: public task::Task
{
public:
   Vp3Sim( const std::string& taskName );
   virtual ~Vp3Sim( );

   virtual bool initialize( );
   virtual bool executive( );
   virtual void cleanup( );
protected:
private:

   void Vp3SimSendFileAttr( unsigned_32 FileNumber );
   void Vp3SimSendFileAttrRespRead( );

   FileTransferBridgeResponseInput  *FileTransferBridgeResponseInput_;
   FileTransferBridgeRequestOutput *FileTransferBridgeRequestOutput_;
   bool IsDirectory( const char *path );
   void CreateFile(const char* fileName, unsigned_32 size);
   Ret_t MakeDirFullPath(const char *path, mode_t mode);

   string m_DefaultDataFilePath;
   unsigned_32 m_FileCountTarget;
   unsigned_32 m_FileCountCurrent;
   unsigned_32 m_FileSize;
   bool m_RunSftTest;
   std::vector<unsigned_32> m_FileTypes;

};

#endif
