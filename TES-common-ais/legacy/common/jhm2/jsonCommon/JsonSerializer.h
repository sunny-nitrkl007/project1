///////////////////////////////////////////////////////////////////////////////
/// @file      JsonSerializer.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     JSON serialization of base types
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONSERIALIZER_H_
#define JSONSERIALIZER_H_

#include <string>
#include <list>
#include <vector>
#include <map>
#include <rapidjson/writer.h>
#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/utility/enable_if.hpp>
#include <util/FlagContainer.h>
#include "JsonDecodeException.h"

namespace jhm2
{
  namespace json
  {
    ///////////////////////////////////////////////////////////////////////
    //Template magic to automatically deference pointers, and handle enums
    ///////////////////////////////////////////////////////////////////////
    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, typename boost::enable_if< boost::is_pointer< T > >::type* dummy = 0 )
    {
        out.StartObject();
        val->jsonSerialize(out);
        out.EndObject();
    }

    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, typename boost::enable_if< boost::is_enum< T > >::type* dummy = 0 )
    {
        int temp = static_cast<int>(val);
        out.Int( temp );
    }

    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, typename boost::disable_if< boost::type_traits::ice_or<
                       boost::is_enum< T >::value, boost::is_pointer< T >::value > >::type* dummy = 0 )
    {
        out.StartObject();
        val.jsonSerialize(out);
        out.EndObject();
    }

    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, FlagContainer& fc, typename boost::enable_if< boost::is_pointer< T > >::type* dummy = 0 )
    {
        out.StartObject();
        val->jsonSerialize(out,fc);
        out.EndObject();
    }

    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, FlagContainer& fc, typename boost::enable_if< boost::is_enum< T > >::type* dummy = 0 )
    {
        int temp = static_cast<int>(val);
        out.Int( temp );
    }

    template < class Writer, class T >
    void base_serialize( Writer& out, T& val, FlagContainer& fc, typename boost::disable_if< boost::type_traits::ice_or<
                       boost::is_enum< T >::value, boost::is_pointer< T >::value > >::type* dummy = 0 )
    {
        out.StartObject();
        val.jsonSerialize(out,fc);
        out.EndObject();
    }

    template < class Reader, class T >
    void base_deserialize( Reader& in, T& val, typename boost::enable_if< boost::is_pointer< T > >::type* dummy = 0 )
    {
        in.StartObject();
        val->jsonSerialize(in);
        in.EndObject();
    }

    template < class Reader, class T >
    void base_deserialize( Reader& in, T& val, FlagContainer& fc, typename boost::enable_if< boost::is_pointer< T > >::type* dummy = 0 )
    {
        in.StartObject();
        val->jsonSerialize(in,fc);
        in.EndObject();
    }

    template < class Reader, class T >
    void base_deserialize( Reader& in, T& val, typename boost::enable_if< boost::is_enum< T > >::type* dummy = 0 )
    {
        if ( !in.IsInt() )
          throw JsonDecodeException("Type not int", in.getPath());

        int temp = in.GetInt();
        val = static_cast<T>(temp);
    }

    template < class Reader, class T >
    void base_deserialize( Reader& in, T& val, typename boost::disable_if< boost::type_traits::ice_or<
                       boost::is_enum< T >::value, boost::is_pointer< T >::value > >::type* dummy = 0 )
    {
        in.StartObject();
        val.jsonSerialize(in);
        in.EndObject();
    }

    template < class Reader, class T >
    void base_deserialize( Reader& in, T& val, FlagContainer& fc, typename boost::disable_if< boost::type_traits::ice_or<
                       boost::is_enum< T >::value, boost::is_pointer< T >::value > >::type* dummy = 0 )
    {
        in.StartObject();
        val.jsonSerialize(in,fc);
        in.EndObject();
    }

    //////////////////////////////////////////////////////

    template< class T >
    class JsonSerializer
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, T& val )
        {
          base_serialize(out,val);
        }

        //Serialize with flag container support
        template< class Writer >
        static void serialize( Writer& out, T& val, FlagContainer& fc )
        {
          base_serialize(out,val,fc);
        }

        template< class Reader >
        static void deserialize( Reader& in, T& val )
        {
          base_deserialize(in,val);
        }

        template< class Reader >
        static void deserialize( Reader& in, T& val, FlagContainer& fc )
        {
          base_deserialize(in,val, fc);
        }

    };

    template<>
    class JsonSerializer< bool >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, bool& val )
        {
          //Default to string
          out.wBool( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, bool& val )
        {
          if ( !in.IsBool() )
            throw JsonDecodeException("Type not bool", in.getPath());

          val = in.GetBool();
        }
    };

    template<>
    class JsonSerializer< std::string >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, std::string& val )
        {
          out.String( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, std::string& val )
        {
          if ( !in.IsString() )
            throw JsonDecodeException("Type not string", in.getPath());

          val = in.GetString();
        }
    };

    template<>
    class JsonSerializer< unsigned int >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, unsigned int& val )
        {
          out.Uint( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, unsigned int& val )
        {
          if ( !in.IsUint() )
            throw JsonDecodeException("Type not uint", in.getPath());

          val = in.GetUint();
        }
    };

    template<>
    class JsonSerializer< int >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, int& val )
        {
          out.Int( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, int& val )
        {
          if ( !in.IsInt() )
            throw JsonDecodeException("Type not int", in.getPath());

          val = in.GetInt();
        }
    };

    template<>
    class JsonSerializer< unsigned long int >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, unsigned long int& val )
        {
          out.Uint( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, unsigned long int& val )
        {
          if ( !in.IsUint() )
            throw JsonDecodeException("Type not uint", in.getPath());

          val = in.GetUint();
        }
    };

    template<>
    class JsonSerializer< long int >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, long int& val )
        {
          out.Int( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, long int& val )
        {
          if ( !in.IsInt() )
            throw JsonDecodeException("Type not int", in.getPath());

          val = in.GetInt();
        }
    };

    template<>
    class JsonSerializer< unsigned short >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, unsigned short& val )
        {
          out.Uint( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, unsigned short& val )
        {
          if ( !in.IsUint() )
            throw JsonDecodeException("Type not uint", in.getPath());

          val = in.GetUint();
        }
    };

    template<>
    class JsonSerializer< short >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, short& val )
        {
          out.Int( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, short& val )
        {
          if ( !in.IsInt() )
            throw JsonDecodeException("Type not int", in.getPath());

          val = in.GetInt();
        }
    };

    template<>
    class JsonSerializer< unsigned char >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, unsigned char& val )
        {
          out.Uint( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, unsigned char& val )
        {
          if ( !in.IsUint() )
            throw JsonDecodeException("Type not uint", in.getPath());

          val = in.GetUint();
        }
    };

    template<>
    class JsonSerializer< char >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, char& val )
        {
          out.Int( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, char& val )
        {
          if ( !in.IsInt() )
            throw JsonDecodeException("Type not int", in.getPath());

          val = in.GetInt();
        }
    };

    template<>
    class JsonSerializer< unsigned long long >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, unsigned long long& val )
        {
          out.Uint64( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, unsigned long long& val )
        {
          if ( !in.IsUint64() )
            throw JsonDecodeException("Type not uint64", in.getPath());

          val = in.GetUint64();
        }
    };

    template<>
    class JsonSerializer< long long >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, long long& val )
        {
          out.Int64( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, long long& val )
        {
          if ( !in.IsInt64() )
            throw JsonDecodeException("Type not int64", in.getPath());

          val = in.GetInt64();
        }
    };

    template<>
    class JsonSerializer< float >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, float& val )
        {
          out.Double( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, float& val )
        {
          if ( !in.IsDouble() )
            throw JsonDecodeException("Type not float", in.getPath());

          val = in.GetDouble();
        }
    };

    template<>
    class JsonSerializer< double >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, double& val )
        {
          out.Double( val );
        }

        template< class Reader >
        static void deserialize( Reader& in, double& val )
        {
          if ( !in.IsDouble() )
            throw JsonDecodeException("Type not float", in.getPath());

          val = in.GetDouble();
        }
    };

  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONSERIALIZER_H_ */
