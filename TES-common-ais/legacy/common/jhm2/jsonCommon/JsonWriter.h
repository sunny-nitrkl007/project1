///////////////////////////////////////////////////////////////////////////////
/// @file      JsonWriter.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     Wrapper type for RapidJson Writer
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONWRITER_H_
#define JSONWRITER_H_

#include <rapidjson/writer.h>
#include <jhm2/jsonCommon/JsonStreamBuf.h>

namespace jhm2
{
  namespace json
  {
    
    class JsonWriter: public rapidjson::Writer<JsonStreamBuf>
    {
      public:
        JsonWriter ( jhm2::json::JsonStreamBuf& buf ): rapidjson::Writer<JsonStreamBuf>( buf ) {}
        virtual ~JsonWriter () {}

        virtual void responseStart( const std::string& responseName )
        {
          StartObject();
          String( responseName );
          StartObject();
        }

        virtual void responseEnd( )
        {
          EndObject();
          EndObject();
        }
    };
  
  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONWRITER_H_ */
