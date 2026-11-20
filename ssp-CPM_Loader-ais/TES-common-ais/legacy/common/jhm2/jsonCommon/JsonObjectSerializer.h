///////////////////////////////////////////////////////////////////////////////
/// @file      JsonObjectSerializer.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     JSON serialization of basic key value pair
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONOBJECTSERIALIZER_H_
#define JSONOBJECTSERIALIZER_H_

#include <jhm2/jsonCommon/JsonSerializer.h>
#include <boost/utility/value_init.hpp>
#include <util/FlagContainer.h>

namespace jhm2
{
  namespace json
  {
    
    template< class T >
    class JsonObjectSerializer
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, const std::string& key, T& val )
        {
          //At it's simplest form, a json object is simply a key value pair
          out.String( key );  //key
          JsonSerializer<T>::serialize( out, val ); //val
        }

        template< class Writer >
        static void serialize( Writer& out, const std::string& key, T& val, FlagContainer& fc )
        {
          //At it's simplest form, a json object is simply a key value pair
          out.String( key );  //key
          JsonSerializer<T>::serialize( out, val, fc ); //val
        }

        template< class Reader >
        static void deserialize( Reader& in, const std::string& key, T& val )
        {
          //Advance to this key
          in.Key(key);
          //And deserialize it
          return JsonSerializer<T>::deserialize( in, val );
        }

        template< class Reader >
        static void deserialize( Reader& in, const std::string& key, T& val, FlagContainer& fc )
        {
          //Advance to this key
          in.Key(key);
          //And deserialize it
          return JsonSerializer<T>::deserialize( in, val, fc );
        }
    };

  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONOBJECTSERIALIZER_H_ */
