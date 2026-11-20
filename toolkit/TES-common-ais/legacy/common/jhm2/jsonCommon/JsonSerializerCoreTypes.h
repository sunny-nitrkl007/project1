///////////////////////////////////////////////////////////////////////////////
/// @file      JsonSerializerCoreTypes.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     JSON serialization of common core types
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONSERIALIZERCORETYPES_H_
#define JSONSERIALIZERCORETYPES_H_

#include <jhm2/jsonCommon/JsonObjectSerializer.h>
#include <geometry/primitives/Angle.h>
#include <geometry/primitives/Vector2D.h>
#include <geometry/primitives/Vector3D.h>
#include <geometry/poses/Pose2D.h>
#include <geometry/poses/ISOPose3D.h>
#include <ais/time/TimeStamp.h>

#include <vector>
#include <list>
#include <map>

namespace jhm2
{
  namespace json
  {
    template< class T >
    class JsonSerializer< nrec::geometry::Angle<T> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, nrec::geometry::Angle<T>& val )
        {
          T temp = val.getRadians();
          JsonSerializer<T>::serialize( out, temp );
        }

        template< class Reader >
        static void deserialize( Reader& in, nrec::geometry::Angle<T>& val )
        {
          T temp;
          JsonSerializer<T>::deserialize( in, temp );
          val.setRadians(temp);
        }
    };

    template< class T >
    class JsonSerializer< nrec::geometry::Vector2D<T> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, nrec::geometry::Vector2D<T>& val )
        {
          out.StartObject();
          JsonObjectSerializer<T>::serialize( out, "x", val.x() );
          JsonObjectSerializer<T>::serialize( out, "y", val.y() );
          out.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, nrec::geometry::Vector2D<T>& val )
        {
          in.StartObject();
          JsonObjectSerializer<T>::deserialize( in, "x", val.x() );
          JsonObjectSerializer<T>::deserialize( in, "y", val.y() );
          in.EndObject();
        }
    };

    template< class T >
    class JsonSerializer< nrec::geometry::Vector3D<T> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, nrec::geometry::Vector3D<T>& val )
        {
          out.StartObject();
          JsonObjectSerializer<T>::serialize( out, "x", val.x() );
          JsonObjectSerializer<T>::serialize( out, "y", val.y() );
          JsonObjectSerializer<T>::serialize( out, "z", val.z() );
          out.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, nrec::geometry::Vector3D<T>& val )
        {
          in.StartObject();
          JsonObjectSerializer<T>::deserialize( in, "x", val.x() );
          JsonObjectSerializer<T>::deserialize( in, "y", val.y() );
          JsonObjectSerializer<T>::deserialize( in, "z", val.z() );
          in.EndObject();
        }
    };
    
    template< class T >
    class JsonSerializer< nrec::geometry::Pose2D<T> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, nrec::geometry::Pose2D<T>& val )
        {
          out.StartObject();
          JsonObjectSerializer< nrec::geometry::Vector2D<T> >::serialize( out, "position", val.getPosition() );
          JsonObjectSerializer< nrec::geometry::Angle<T> >::serialize( out, "orientation", val.orientation().getRadians() );
          out.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, nrec::geometry::Pose2D<T>& val )
        {
          in.StartObject();
          JsonObjectSerializer< nrec::geometry::Vector2D<T> >::deserialize( in, "position", val.getPosition() );
          T temp;
          JsonObjectSerializer< nrec::geometry::Angle<T> >::deserialize( in, "orientation", temp );
          val.orientation().setRadians( temp );
          in.EndObject();
        }
    };

    template< class T >
    class JsonSerializer< nrec::geometry::ISOPose3D<T> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, nrec::geometry::ISOPose3D<T>& val )
        {
          out.StartObject();
            nrec::geometry::Vector3D<T> temp = val.getPosition();
            JsonObjectSerializer< nrec::geometry::Vector3D<T> >::serialize( out, "position", temp );
            out.String("orientation");
            out.StartObject();
              JsonObjectSerializer< nrec::geometry::Angle<T> >::serialize( out, "roll", val.roll() );
              JsonObjectSerializer< nrec::geometry::Angle<T> >::serialize( out, "pitch", val.pitch() );
              JsonObjectSerializer< nrec::geometry::Angle<T> >::serialize( out, "yaw", val.yaw() );
            out.EndObject();
          out.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, nrec::geometry::ISOPose3D<T>& val )
        {
          in.StartObject();
            nrec::geometry::Vector3D<T> tPosition;
            JsonObjectSerializer< nrec::geometry::Vector3D<T> >::deserialize( in, "position", tPosition );
            val.setPosition( tPosition );
            in.Key("orientation");
            in.StartObject();
              JsonObjectSerializer< nrec::geometry::Angle<T> >::deserialize( in, "roll", val.roll() );
              JsonObjectSerializer< nrec::geometry::Angle<T> >::deserialize( in, "pitch", val.pitch() );
              JsonObjectSerializer< nrec::geometry::Angle<T> >::deserialize( in, "yaw", val.yaw() );
            in.EndObject();
          in.EndObject();
        }
    };

    template<>
    class JsonSerializer< TimeStamp >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, TimeStamp& val )
        {
          double temp = val.toDouble();
          JsonSerializer<double>::serialize( out, temp );
        }

        template< class Reader >
        static void deserialize( Reader& in, TimeStamp& val )
        {
          double temp;
          JsonSerializer<double>::deserialize( in, temp );
          val.fromDouble(temp);
        }
    };

    template<class T, class Alloc>
    class JsonSerializer< std::vector<T, Alloc> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, std::vector<T, Alloc>& val )
        {
          out.StartArray();
          for ( unsigned int i = 0; i < val.size(); ++i )
          {
            JsonSerializer<T>::serialize(out, val.at(i));
          }
          out.EndArray();
        }

        template< class Writer >
        static void serialize( Writer& out, std::vector<T, Alloc>& val, FlagContainer& fc )
        {
          out.StartArray();
          for ( unsigned int i = 0; i < val.size(); ++i )
          {
            JsonSerializer<T>::serialize(out, val.at(i), fc);
          }
          out.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::vector<T, Alloc>& val )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            T newVal;
            JsonSerializer<T>::deserialize(in, newVal);
            val.push_back(newVal);
          }
          in.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::vector<T, Alloc>& val, FlagContainer& fc )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            T newVal;
            JsonSerializer<T>::deserialize(in, newVal, fc);
            val.push_back(newVal);
          }
          in.EndArray();
        }
    };

    template<class T, class Alloc>
    class JsonSerializer< std::list<T, Alloc> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, std::list<T, Alloc>& val )
        {
          out.StartArray();
          for ( typename std::list<T,Alloc>::iterator it = val.begin(); it != val.end(); ++it )
          {
            JsonSerializer<T>::serialize(out, *it);
          }
          out.EndArray();
        }

        template< class Writer >
        static void serialize( Writer& out, std::list<T, Alloc>& val, FlagContainer& fc )
        {
          out.StartArray();
          for ( typename std::list<T,Alloc>::iterator it = val.begin(); it != val.end(); ++it )
          {
            JsonSerializer<T>::serialize(out, *it, fc);
          }
          out.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::list<T, Alloc>& val )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            T temp;
            JsonSerializer<T>::deserialize(in, temp);
            val.push_back(temp);
          }
          in.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::list<T, Alloc>& val, FlagContainer& fc )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            T temp;
            JsonSerializer<T>::deserialize(in, temp, fc);
            val.push_back(temp);
          }
          in.EndArray();
        }
    };

    template<class T1, class T2>
    class JsonSerializer< std::pair<T1, T2> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, std::pair<T1, T2>& val )
        {
           out.StartObject();
           JsonObjectSerializer<T1>::serialize(out, "first", val.first);
           JsonObjectSerializer<T2>::serialize(out, "second", val.second);
           out.EndObject();
        }

        template< class Writer >
        static void serialize( Writer& out, std::pair<T1, T2>& val, FlagContainer& fc )
        {
           out.StartObject();
           JsonObjectSerializer<T1>::serialize(out, "first", val.first, fc);
           JsonObjectSerializer<T2>::serialize(out, "second", val.second, fc);
           out.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::pair<T1, T2>& val )
        {
           in.StartObject();
           JsonObjectSerializer<T1>::deserialize(in, "first", val.first);
           JsonObjectSerializer<T2>::deserialize(in, "second", val.second);
           in.EndObject();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::pair<T1, T2>& val, FlagContainer& fc )
        {
           in.StartObject();
           JsonObjectSerializer<T1>::deserialize(in, "first", val.first, fc);
           JsonObjectSerializer<T2>::deserialize(in, "second", val.second, fc);
           in.EndObject();
        }
    };

    template<class Key, class T, class Compare, class Alloc>
    class JsonSerializer< std::map<Key, T, Compare, Alloc> >
    {
      public:
        template< class Writer >
        static void serialize( Writer& out, std::map<Key, T, Compare, Alloc>& val )
        {
          out.StartArray();
          for ( typename std::map<Key,T,Compare,Alloc>::iterator it = val.begin(); it != val.end(); ++it )
          {
            std::pair<Key,T> temp = *it;
            JsonSerializer< std::pair<Key,T> >::serialize(out, temp);
          }
          out.EndArray();
        }

        template< class Writer >
        static void serialize( Writer& out, std::map<Key, T, Compare, Alloc>& val, FlagContainer& fc )
        {
          out.StartArray();
          for ( typename std::map<Key,T,Compare,Alloc>::iterator it = val.begin(); it != val.end(); ++it )
          {
            std::pair<Key,T> temp = *it;
            JsonSerializer< std::pair<Key,T> >::serialize(out, temp, fc);
          }
          out.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::map<Key, T, Compare, Alloc>& val )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            std::pair<Key,T> temp;
            JsonSerializer< std::pair<Key,T> >::deserialize(in, temp);
            val.insert(temp);
          }
          in.EndArray();
        }

        template< class Reader >
        static void deserialize( Reader& in, std::map<Key, T, Compare, Alloc>& val, FlagContainer& fc )
        {
          if( !in.IsArray() )
            throw JsonDecodeException("Type not array", in.getPath());

          in.StartArray();
          for ( unsigned int i = 0; i < in.Capacity(); ++i )
          {
            in.IndexArray(i);
            std::pair<Key,T> temp;
            JsonSerializer< std::pair<Key,T> >::deserialize(in, temp, fc);
            val.insert(temp);
          }
          in.EndArray();
        }
    };

  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONSERIALIZERCORETYPES_H_ */
