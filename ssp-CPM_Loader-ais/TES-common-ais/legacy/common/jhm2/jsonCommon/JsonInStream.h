///////////////////////////////////////////////////////////////////////////////
/// @file      JsonInStream.h
/// @author    strubjc
/// @date      Apr 6, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONINSTREAM_H_
#define JSONINSTREAM_H_

#include <jhm2/jsonCommon/JsonSerializerCoreTypes.h>
#include <jhm2/jsonCommon/JsonObjectSerializer.h>
#include <jhm2/jsonCommon/JsonStringStream.h>
#include <jhm2/jsonCommon/JsonReader.h>
#include <util/FlagContainer.h>
#include <jhm2/jsonCommon/JsonIosAbstractBase.h>

class JsonInStream: public JsonIosAbstractBase, public jhm2::json::JsonReader
{
  public:
    JsonInStream (const std::string& in):
      JsonIosAbstractBase( JsonIosAbstractBase::INPUT ),
      jhm2::json::JsonReader( in ) {}
    virtual  ~JsonInStream () {}

    //!Operator to set value from the Json stream.
    template<typename T>
    void jsonImpl(const std::string& key, T& value)
    {
      jhm2::json::JsonObjectSerializer<T>::deserialize( *this, key, value );
    }

    //!Operator to set value from the Json stream.
    template<typename T>
    void jsonImpl(const std::string& key, T& value, FlagContainer& fc )
    {
      jhm2::json::JsonObjectSerializer<T>::deserialize( *this, key, value, fc );
    }

  private:
};

#endif /* JSONINSTREAM_H_ */
