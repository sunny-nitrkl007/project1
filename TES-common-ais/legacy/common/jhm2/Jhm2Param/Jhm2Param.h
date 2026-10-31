///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2Param.h
/// @author    strubjc
/// @date      Mar 21, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2PARAM_H_
#define JHM2PARAM_H_

#include <jhm2/jsonCommon/JsonIosBase.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class Jhm2Param
{
  public:
    Jhm2Param(): m_name( "" ), m_dsi( 0 ) {}
    Jhm2Param( const std::string& name ): m_name( name ), m_dsi( 0 ) {}
    Jhm2Param( const std::string& name, const unsigned char& dsi ): m_name( name ), m_dsi( dsi ) {}
    virtual ~Jhm2Param() {}

    virtual std::string getName() const { return m_name; }
    virtual std::string getType() const =0;

    virtual void getXml( std::ostream& xml ) const =0;


    virtual void jsonSerializeImpl( JsonIosAbstractBase& json )
    {
      json(getType(), *this);
    }

    //Probably should be pure, but need to impelment this in all the classes that derive from Jhm2Param
    virtual void jsonSerialize( JsonIosAbstractBase& json ) {}

    virtual void jsonSerialize2(rapidjson::Writer<rapidjson::StringBuffer>& writer) const = 0;

//    virtual void jsonSerialize( JsonIosAbstractBase& json )
//    {
//      if ( !m_name.empty() )
//      {
//        json("Name", m_name);
//      }
//
//      jsonDerializeDsi(json);
//    }

    void jsonSerializeDsi( JsonIosAbstractBase& json )
    {
      if ( m_dsi != 0 )
      {
        unsigned int tmpDsi = static_cast<unsigned int>( m_dsi );
        json("Dsi", tmpDsi );
      }
    }

    virtual void getXmlStart( std::ostream& xml ) const
    {
      xml << "<" << getType() << " name=\"" << m_name << "\">";
    }

    virtual void getXmlEnd( std::ostream& xml ) const
    {
      xml << "<Dsi>";
      if ( m_dsi != 0 )
        xml << static_cast<unsigned int>( m_dsi );
      xml << "</Dsi>";
      xml << "</" << getType() << ">";
    }

  protected:
    std::string     m_name;
    unsigned char   m_dsi;
};


#endif /* JHM2PARAM_H_ */
