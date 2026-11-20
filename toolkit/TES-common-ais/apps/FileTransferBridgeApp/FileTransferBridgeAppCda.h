
 ////////////////////////////////////////////////////////
 //
 // Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
 //
 //     Class: FileTransferBridgeAppCda
 //
 // File Name: FileTransferBridgeAppCda.h
 //
 //  Abstract: Declaration of the class that acts as
 //            a CDA Client layer between the CDA Server
 //            and (this) Bridge application
 //
 ////////////////////////////////////////////////////////
 
 #ifndef SCSCDATTIBRIDGECDA_H
 #define SCSCDATTIBRIDGECDA_H
 
 // STL includes
 #include <memory>       // Needed for std::unique_ptr
 #include <string>       // Needed for std::string
 #include <mutex>        // Needed for std::mutex
 #include <functional>   // Needed for std::function
 #include <thread>       // Needed for std::thread and std::this_thread::get_id() (expanded from THREAD_ID)
 
 #include <grpc++/support/stub_options.h>
 #include <chrono>
 #include <iostream>
 #include <memory>
 #include <random>
 #include <string>
 #include <thread>
 #include <unistd.h>

 #include <grpc++/security/credentials.h>
 
 // Probobuf/GRPC includes
 #include <grpc++/grpc++.h>
 #include <grpc/grpc.h>
 #include <grpc++/channel.h>
 #include <grpc++/client_context.h>
 #include <grpc++/create_channel.h>
 #include <grpc++/security/credentials.h>
 #include <CDATelematicsTransfer.pb.h>
 #include <CDATelematicsTransfer.grpc.pb.h>
 #include <CDASystemFileTransfer.pb.h>
 #include <CDASystemFileTransfer.grpc.pb.h>
 #include <CDAParameterConsumer.pb.h>
 #include <CDAParameterConsumer.grpc.pb.h>
 #include <ReportTrigger.pb.h>
 
 // App includes
 #include "FileTransferBridgeAppLog.h"
 #include "FileTransferBridgeAppDef.h"
 #include "FileTransferBridgeAppUtil.h"
 
 #define NO_NODE 0
 #define ALL_SFT_NODES 0xDEADBEEF // Something that FileTransferBridgeAppUtil::IsSFTNode() will pick up and unlikely to be an actual FID
 #define TRIGGER_TYPE 10352       // Telematics File Number than indicates a Report Trigger
 
 using namespace std;
 using namespace CDA::ParameterConsumer;

 using grpc::Channel;
 using grpc::ClientContext;
 using grpc::Status;

 class FileTransferBridgeAppCda
 {
 public:
    // The following structure includes all attributes required for a stream operation between CDA/TTI server and CDA client
    typedef struct RxStreamAttributesTti_s
    {
       const FileTransferBridge::CdaNode_t                         node;                      // Node services by the stream
       std::unique_ptr< grpc::ClientReader
          <CDA::TelematicsTransfer::DestinationMessage> >          pCdaTransactionReader;     // gRPC Client Reader
       grpc::ClientContext                                         clientContext;             // gRPC Client Context
       CDA::TelematicsTransfer::DestinationFilter                  fileFilter;                // Rx source and file type filter object
 
       // Structure constructor; sets the Rx source and file type filter
       RxStreamAttributesTti_s( const std::vector<FileTransferBridge::CdaFileType_t> fileTypes, const FileTransferBridge::CdaNode_t node ):
          node { node },
          pCdaTransactionReader { nullptr },
          clientContext { },
          fileFilter { }
       {
          for ( auto& fileType : fileTypes )
          {
             fileFilter.add_filetypegroup( static_cast<google::protobuf::uint32>( fileType ) );
          }
          fileFilter.set_destination( static_cast<CDA::TelematicsTransfer::DestinationMessage_DESTINATION>( node ) );
       }
       RxStreamAttributesTti_s() = delete;
    } RxStreamAttributesTti_t;
 
    // The following structure includes all attributes required for a stream operation between CDA/SFT server and CDA client
    typedef struct RxStreamAttributesSft_s
    {
       std::unique_ptr< grpc::ClientReader
          <CDA::SystemFileTransfer::SystemFileDestination> >       pCdaTransactionReader;     // gRPC Client Reader
       grpc::ClientContext                                         clientContext;             // gRPC Client Context
       CDA::SystemFileTransfer::SystemFileFilter                   fileFilter;                // Rx source and file type filter object
 
       // Structure constructor; sets the FID (source or Rx) and file type filter
       RxStreamAttributesSft_s( const std::vector<FileTransferBridge::CdaFileType_t> fileTypes, const FileTransferBridge::CdaNodeList_t& nodesFilter ):
          pCdaTransactionReader { nullptr },
          clientContext { },
          fileFilter { }
       {
          for ( auto& fileType : fileTypes )
          {
             fileFilter.add_filetypegroup( static_cast<google::protobuf::uint32>( fileType ) );
          }
          for ( auto& node : nodesFilter )
          {
             fileFilter.add_fidgroup( static_cast<google::protobuf::uint32>( node ) );
          }
       }
       RxStreamAttributesSft_s() = delete;
    } RxStreamAttributesSft_t;
 
    // Structure that defines the ReportTrigger attributes
    typedef struct Trigger_s
    {
       FileTransferBridge::CdaNode_t sourceNodeFid; // CDA node (FID) that sent the trigger
       CAT::FileTransfer::ReportTrigger::COMMAND triggerCommand; // Trigger command type
       google::protobuf::uint32 triggerFileType; // File type associated with the ReportTrigger
       google::protobuf::uint32 triggerSource; // Actual source of the trigger at the CDA node (e.g. Web Page)
       google::protobuf::uint32 message_id;
	} Trigger_t;
 
    enum class SendDataFileReturnCode : uint8_t {
        OK,
        BAD_FILE,
        FILE_TYPE_NOT_SUPPORTED,
        SERVICE_ERROR,
        MULTIPLE_ERRORS,
        UNKNOWN
    };
 
    FileTransferBridgeAppCda( bool isConnectionSecure, const std::string& certChain, const std::string& newServerIP, const std::string& newServerPort );
	~FileTransferBridgeAppCda( );
 
    SendDataFileReturnCode SendDataFile(const FileTransferBridge::FileInfo_t& fileInfo,
          const std::string& fileContentBuf,
          const FileTransferBridge::CdaNodeList_t& nodes,
          const FileTransferBridge::CdaNode_t& defaultFid);
    bool ReceiveDataFile( const volatile bool& stopFlag, RxStreamAttributesTti_t& attrib, std::string& fileContentBuf, FileTransferBridge::CdaFileType_t& fileTypeBuf, std::string& filenameBuf );
    bool ReceiveDataFile( const volatile bool& stopFlag,
          RxStreamAttributesSft_t& attrib,
          const std::map<FileTransferBridge::CdaFileType_t, FileTransferBridge::CdaFileProperties_t>& mapFileTypeToProperties,
          std::string& fileContentBuf,
          FileTransferBridge::CdaFileType_t& fileTypeBuf,
          FileTransferBridge::CdaNode_t& fileSourceBuf,
          FileTransferBridge::CdaNode_t& fileDestBuf,
          std::function< bool( const Trigger_t& ) > triggerCallback );
    bool RegisterForFileType( RxStreamAttributesTti_t& attrib );
    bool RegisterForFileType( RxStreamAttributesSft_t& attrib );
    bool ConnectToCDAServer( void );
    bool IsConnActive( const FileTransferBridge::CdaNode_t node = NO_NODE );
    void SetConnInactive( const FileTransferBridge::CdaNode_t node = NO_NODE );
 
    inline const std::shared_ptr<grpc::Channel>& getChannel() const { return m_spChannel; }
    
	bool ServerStat() {return m_ServerOnline;}
    bool SFTCOnnection() {return m_SftAttributes.connectionEstablished;}
    bool TTIConnection() {return m_TtiAttributes.connectionEstablished;}
   
 private:
    // This structure defines attributes that could be associated with each CDA server
    typedef struct CommonServerAttributes_s
    {
       volatile bool                                connectionInProgress;   // Flag that is set by a connection thread to indicate that connection is in progress
       volatile bool                                connectionEstablished;  // Flag that is set by a connection thread to indicate that connection is established
       std::unique_ptr<std::thread>                 connectionThreadHandle; // Connection thread handle that is used by the main thread
       std::mutex                                   lockStub;               // Mutex that is used for CDA stub protection between threads
       const std::chrono::system_clock::time_point  cdaClientStartupTime;   // Debug/log field that holds the CDA client start-up time
       CommonServerAttributes_s():
             connectionInProgress( false ),
             connectionEstablished( false ),
             connectionThreadHandle( nullptr ),
             cdaClientStartupTime( FileTransferBridgeAppUtil::GetTimeNow() ) { }
    } CommonServerAttributes_t;
    const bool                                                           m_ConnSecure;
    std::mutex                                                           m_LockChannel;
    const std::string                                                    m_CertificateChainFile;
    const std::string                                                    m_ServerIPAddress;
	const std::string                                                    m_ServerPort;
    bool                                                                 m_ServerOnline;
    CommonServerAttributes_t                                             m_SftAttributes;
    CommonServerAttributes_t                                             m_TtiAttributes;
 
    // Telematics members
    std::unique_ptr<CDA::TelematicsTransfer::TelematicsTransfer::Stub>   m_spCdaTtiServerStub;
    std::unique_ptr<CDA::SystemFileTransfer::SystemFileTransfer::Stub>   m_spCdaSftServerStub;
    std::shared_ptr<grpc::Channel>                                       m_spChannel;
 
    bool ConnectOpenChannel( void );
    void ConnectTtiThreadImplementation( void );
    void ConnectSftThreadImplementation( void );
 
    bool GetCDAServerDnsFromIP( const std::string& ipAddr, std::string& CDAServerDns );
 
    SendDataFileReturnCode SendDataFileTti(const std::string& name, const CDA::TelematicsTransfer::TransferMessage& contents, const FileTransferBridge::CdaNode_t& destination);
    SendDataFileReturnCode SendDataFileSft(const std::string& name, const CDA::SystemFileTransfer::SystemFile& contents, const FileTransferBridge::CdaNode_t& destination);
 
    void UpdateSendDataFileReturnCode(SendDataFileReturnCode& code, const SendDataFileReturnCode& newCode);
 };
 
 #endif // SCSCDATTIBRIDGECDA_H
