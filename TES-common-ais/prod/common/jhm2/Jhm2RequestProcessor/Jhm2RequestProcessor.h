///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2RequestProcessor.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2REQUESTPROCESSOR_H_
#define JHM2REQUESTPROCESSOR_H_

#include <string>
#include <ais/config/TaskParser.h>
#include <jhm2/Jhm2Param/Jhm2ParamMsgRequest.h>
#include <jhm2/Jhm2Param/Jhm2ParamMsg.h>
#include <jhm2/Jhm2Param/Jhm2ImageMsg.h>

class Jhm2RequestProcessor
{
  public:
    Jhm2RequestProcessor();
    virtual ~Jhm2RequestProcessor();

    virtual bool processRequest( const std::string& req, std::string& resp );
    virtual bool processRequest( const Jhm2ParamMsgRequest& request, std::string& resp );
    virtual std::string getEndpoint() const;

  protected:
    virtual bool configure( TaskParser& cp )=0;
    virtual bool update( )=0;

    virtual Jhm2Msg* getResponse( const Jhm2ParamMsgRequest& req )=0;

  private:

};

#endif /* JHM2REQUESTPROCESSOR_H_ */
