///////////////////////////////////////////////////////////////////////////////
/// @file      JsonOutStream.h
/// @author    strubjc
/// @date      Dec 14, 2015
/// @brief     OutStream used by Jsonable typetrait
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONOUTSTREAM_H_
#define JSONOUTSTREAM_H_

#include <jhm2/jsonCommon/JsonSerializerCoreTypes.h>
#include <jhm2/jsonCommon/JsonObjectSerializer.h>
#include <jhm2/jsonCommon/JsonStreamBuf.h>
#include <jhm2/jsonCommon/JsonWriter.h>
#include <util/FlagContainer.h>
#include <jhm2/jsonCommon/JsonIosAbstractBase.h>

class JsonOutStream: public JsonIosAbstractBase, public jhm2::json::JsonWriter
{
  public:
    JsonOutStream ( ):
      JsonIosAbstractBase( JsonIosAbstractBase::OUTPUT ),
      jhm2::json::JsonWriter( m_buf ) {}
    virtual ~JsonOutStream () {}

    //!Operator to output object into the Json stream.
    template<typename T>
    void jsonImpl(const std::string& key, T& value)
    {
      jhm2::json::JsonObjectSerializer<T>::serialize( *this, key, value );
    }

    //!Operator to output object into the Json stream, with flagContainer
    template<typename T>
    void jsonImpl(const std::string& key, T& value, FlagContainer& fc )
    {
      jhm2::json::JsonObjectSerializer<T>::serialize( *this, key, value, fc );
    }

    friend std::ostream &operator<<( std::ostream &output, const JsonOutStream &jos )
    {
       output << jos.m_buf.GetString();
       return output;
    }

  protected:
    jhm2::json::JsonStreamBuf m_buf;
};


#endif /* JSONOUTSTREAM_H_ */
