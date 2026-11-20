///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2SimpleParam.h
/// @author    strubjc
/// @date      Mar 21, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2SIMPLEPARAM_H_
#define JHM2SIMPLEPARAM_H_

#include "Jhm2Param.h"
#include "XmlTypeConverters.h"

class Jhm2SimpleParam: public Jhm2Param
{
  public:
    Jhm2SimpleParam(): Jhm2Param( ), m_value( ) {}
    Jhm2SimpleParam( const std::string& name, const std::string& value ): Jhm2Param( name ), m_value( value ) {}
    Jhm2SimpleParam( const std::string& name, const double& value ): Jhm2Param( name )
    {
      m_value = XmlTypeConverters::toXmlStr( value );
    }
    Jhm2SimpleParam( const std::string& name, const unsigned char& dsi, const std::string& value ): Jhm2Param( name, dsi ), m_value( value ) {}
    Jhm2SimpleParam( const std::string& name, const unsigned char& dsi, const double& value ): Jhm2Param( name, dsi )
    {
      m_value = XmlTypeConverters::toXmlStr( value );
    }
    virtual ~Jhm2SimpleParam() {}

    static std::string getStaticType() { return "Param"; }
    virtual std::string getType() const { return Jhm2SimpleParam::getStaticType(); }

    virtual void getXml( std::ostream& xml ) const
    {
      Jhm2Param::getXmlStart( xml );
      xml << "<Value>" << m_value << "</Value>";
      Jhm2Param::getXmlEnd( xml );
    }

    virtual void jsonSerialize( JsonIosAbstractBase& json )
    {
      json(getName(), m_value);
      jsonSerializeDsi(json);
    }

    virtual void jsonSerialize2(rapidjson::Writer<rapidjson::StringBuffer>& writer) const {
        writer.String(getName());
        writer.StartObject();
        writer.Key("value");
        writer.String(m_value); // I guess every SimpleParam is a string?  Whatever.
        if (0 != m_dsi) {
            writer.Key("dsi");
            writer.Uint(m_dsi);
        }
        writer.EndObject();
    }

  private:
    std::string m_value;

};


#endif /* JHM2SIMPLEPARAM_H_ */
