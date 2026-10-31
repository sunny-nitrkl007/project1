///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2ParamMsg.h
/// @author    strubjc
/// @date      Mar 18, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2PARAMMSG_H_
#define JHM2PARAMMSG_H_

#include <string>
#include <vector>
#include <std_types.h>
#include "Jhm2Param.h"
#include "Jhm2Msg.h"
#include <jhm2/jsonCommon/JsonOutStream.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


class Jhm2ParamMsg: public Jhm2Msg
{
  public:
    Jhm2ParamMsg() {}
    virtual ~Jhm2ParamMsg() { clear(); }

    void clear()
    {
      //clear out memory
      for ( unsigned int i = 0; i < m_paramList.size(); ++i )
      {
        delete ( m_paramList.at(i) );
      }
      m_paramList.clear();
    }

    void insertParam( Jhm2Param* newParam ) { m_paramList.push_back( newParam ); }

  protected:
    virtual bool getXml( std::ostream& xml ) const
    {
      xml << "<ParameterList>";
      for ( unsigned int i = 0; i < m_paramList.size(); ++i )
      {
        m_paramList.at(i)->getXml( xml );
      }
      xml << "</ParameterList>";

      return true;
    }

    virtual bool getJson( std::ostream& out ) const
    {
      JsonOutStream jostream;
      jostream.responseStart("ParamMsg");
      jostream.String("ParameterList");
      jostream.StartArray();
      for ( unsigned int i = 0; i < m_paramList.size(); ++i )
      {
        jostream.StartObject();
        m_paramList.at(i)->jsonSerializeImpl(jostream);
        jostream.EndObject();
      }
      jostream.EndArray();
      jostream.responseEnd();
      out << jostream;

      return true;
    }

    virtual bool getJson2(std::ostream& out) const {
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        //writer.SetMaxDecimalPlaces(2);  // Not supported in out version of rapidjson
        writer.StartObject();
        for (const auto& p : m_paramList) {
            p->jsonSerialize2(writer);
        }
        writer.EndObject();

        if (!writer.IsComplete()) {
            return false;
        }

        out << sb.GetString();
        return true;
    }

  private:
    std::vector<Jhm2Param*>   m_paramList;
};

#endif /* JHM2PARAMMSG_H_ */
