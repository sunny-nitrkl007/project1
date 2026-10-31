///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2RequestBuilder.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2REQUESTBUILDER_H_
#define JHM2REQUESTBUILDER_H_

#include <jhm2/Jhm2Ipc/Jhm2IpcClient.h>
#include <string>
#include <jhm2/Jhm2Param/Jhm2ParamMsgRequest.h>

class Jhm2RequestBuilder
{
  public:
    Jhm2RequestBuilder();
    Jhm2RequestBuilder(const std::string& socketPath);
    virtual ~Jhm2RequestBuilder();

    Jhm2ParamMsgRequest& requestMsg();
    std::string& responseData();

    bool sendRequest();

  private:
    bool processRequest( const Jhm2ParamMsgRequest& req, std::string& resp );

    Jhm2ParamMsgRequest m_jhm2RequestMsg;
    std::string         m_responseData;

    bool                m_clientInitialized;
    Jhm2IpcClient       m_ipcClient;

};

#endif /* JHM2REQUESTBUILDER_H_ */
