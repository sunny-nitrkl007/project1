///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2ChannelUpdateResponse.h
/// @author    strubjc
/// @date      Nov 17, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2CHANNELUPDATERESPONSE_H_
#define JHM2CHANNELUPDATERESPONSE_H_

#include "Jhm2Msg.h"
#include "XmlTypeConverters.h"

class Jhm2ChannelUpdateResponse: public Jhm2Msg
{
  public:
    typedef enum
    {
      UPDATE_SUCCESS = 0,
      UPDATE_FAILED
    } ResponseStatusT;

    Jhm2ChannelUpdateResponse (): m_status(UPDATE_FAILED) {}
    Jhm2ChannelUpdateResponse ( const ResponseStatusT& status ): m_status(status)  {}
    Jhm2ChannelUpdateResponse ( const ResponseStatusT& status, const std::string& error ): m_status(status), m_error(error) {}
    virtual ~Jhm2ChannelUpdateResponse () {}

  protected:
    virtual bool getXml( std::ostream& xml ) const
    {
      xml << "<Response>";
      xml << "<Status>" << XmlTypeConverters::toXmlStr(m_status) << "</Status>";
      if ( ( m_status != UPDATE_SUCCESS ) && !m_error.empty() )
      {
        xml << "<Error>" << m_error << "</Error>";
      }
      xml << "</Response>";

      return true;
    }

    virtual bool getJson( std::ostream& out )
    {
      JsonOutStream jostream;
      jostream.responseStart("Response");
      jostream("Status", m_status);
      if ( ( m_status != UPDATE_SUCCESS ) && !m_error.empty() )
      {
        jostream("Error", m_error);
      }
      jostream.responseEnd();
      out << jostream;

      return true;
    }

  private:
    ResponseStatusT m_status;
    std::string     m_error;
};

#endif /* JHM2CHANNELUPDATERESPONSE_H_ */
