///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2ParamMsgRequest.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2PARAMMSGREQUEST_H_
#define JHM2PARAMMSGREQUEST_H_

#include <jhm2/Jhm2Param/Jhm2CgiDatum.h>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <string>

class Jhm2ParamMsgRequestStorage
{
  public:
    Jhm2ParamMsgRequestStorage(): m_requestType( INVALID_REQUEST ), m_reqData(), m_outputFormat( NO_FORMAT ), m_inputFormat( NO_FORMAT ) {}
    virtual ~Jhm2ParamMsgRequestStorage() {}

    typedef enum
    {
      INVALID_REQUEST = 0,
      PARAMETER_MSG_REQUEST,
      IMAGE_MSG_REQUEST,
      COMMAND_MSG_REQUEST,
      CHANNEL_UPDATE_REQUEST,
      FILE_MSG_REQUEST,
      PARAMETER_MSG_REQUEST_2,
      COMMAND_MSG_REQUEST_2
    } eRequestType;


    //Convenience types
    typedef std::set<std::string>           ReqDataT;
    typedef ReqDataT::iterator              ReqDataT_it;
    typedef ReqDataT::const_iterator        ReqDataT_Cit;
    typedef std::pair<std::string,ReqDataT> ReqDataMapElemT;
    typedef std::map<std::string,ReqDataT>  ReqDataMapT;
    typedef ReqDataMapT::iterator           ReqDataMapT_it;
    typedef ReqDataMapT::const_iterator     ReqDataMapT_Cit;

    //Type of this request
    eRequestType      m_requestType;

    //Ancillary data for this request
    ReqDataMapT       m_reqData;

    //Incoming Post Data
    std::string       m_postData;

    typedef enum
    {
      XML_FORMAT=0,
      JSON_FORMAT,
      JSON_FORMAT_2,
      JPG_FORMAT,
      NO_FORMAT
    } eFormat;

    //Output format for response data
    eFormat                                   m_outputFormat;
    //Input format for post data
    eFormat                                   m_inputFormat;

    bool hasReqData( const std::string& paramName ) const
    {
      return ( m_reqData.find( paramName ) != m_reqData.end() );
    }

    const ReqDataT& getReqData( const std::string& param ) const
    {
      if ( hasReqData(param) )
      {
        return m_reqData.at(param);
      } else
      {
        static ReqDataT empty;
        return empty;
      }
    }

    template <class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
      ar & m_requestType & m_reqData & m_outputFormat & m_inputFormat & m_postData;
    }

};

BOOST_CLASS_VERSION(Jhm2ParamMsgRequestStorage, 0)

typedef Jhm2CgiDatum<Jhm2ParamMsgRequestStorage> Jhm2ParamMsgRequest;

#endif /* JHM2PARAMMSGREQUEST_H_ */
