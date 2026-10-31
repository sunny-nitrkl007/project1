///////////////////////////////////////////////////////////////////////////////
/// @file      JsonReader.h
/// @author    strubjc
/// @date      Apr 5, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONREADER_H_
#define JSONREADER_H_

#include <rapidjson/reader.h>
#include <rapidjson/pointer.h>
#include <rapidjson/document.h>
#include <jhm2/jsonCommon/JsonStringStream.h>
#include <ais/log/AisLogger.h>
#include "JsonDecodeException.h"

namespace jhm2
{
  namespace json
  {
    class JsonReadPtr
    {
      public:
        JsonReadPtr( rapidjson::Document& doc ):
          m_doc( doc ),
          m_ptrPath(""),
          m_pCurrentVal( NULL ),
          m_inArray( false ),
          m_arraySize( 0 )
          {
            m_pCurrentVal = rapidjson::Pointer(m_ptrPath.c_str()).Get(m_doc);
          }
        virtual ~JsonReadPtr() {}

        rapidjson::Value& operator()() { return *m_pCurrentVal; }
        const rapidjson::Value& operator()() const { return *m_pCurrentVal; }

        virtual bool IsNull()   const { return m_pCurrentVal->IsNull(); }
        virtual bool IsFalse()  const { return m_pCurrentVal->IsFalse(); }
        virtual bool IsTrue()   const { return m_pCurrentVal->IsTrue(); }
        virtual bool IsBool()   const { return m_pCurrentVal->IsBool(); }
        virtual bool IsObject() const { return m_pCurrentVal->IsObject(); }
        virtual bool IsArray()  const { return m_pCurrentVal->IsArray(); }
        virtual bool IsNumber() const { return m_pCurrentVal->IsNumber(); }
        virtual bool IsInt()    const { return m_pCurrentVal->IsInt(); }
        virtual bool IsUint()   const { return m_pCurrentVal->IsUint(); }
        virtual bool IsInt64()  const { return m_pCurrentVal->IsInt64(); }
        virtual bool IsUint64() const { return m_pCurrentVal->IsUint64(); }
        virtual bool IsDouble() const
        {
          return ( m_pCurrentVal->IsDouble() ||
                   m_pCurrentVal->IsInt() ||
                   m_pCurrentVal->IsUint() ||
                   m_pCurrentVal->IsInt64() ||
                   m_pCurrentVal->IsUint64() );
        }
        virtual bool IsString() const { return m_pCurrentVal->IsString(); }

        virtual int GetBool()    const { return m_pCurrentVal->GetBool(); }
        virtual int GetInt()    const { return m_pCurrentVal->GetInt(); }
        virtual unsigned int GetUint()   const { return m_pCurrentVal->GetUint(); }
        virtual long long GetInt64()  const { return m_pCurrentVal->GetInt64(); }
        virtual unsigned long long GetUint64() const { return m_pCurrentVal->GetUint64(); }
        virtual double GetDouble() const { return m_pCurrentVal->GetDouble(); }
        virtual std::string GetString() const { return m_pCurrentVal->GetString(); }

        virtual unsigned int Capacity() const
        {
          if ( !m_inArray )
          {
            throw JsonDecodeException("Tried to get capacity of Array, but object is not an array", m_ptrPath);
          }

          return m_arraySize;
        }


        virtual bool addKey(const std::string& key)
        {
          //And add the new key
          m_ptrPath += key;
          AIS_LOG_DEBUG("KEY: %s", m_ptrPath.c_str());
          return updatePtr();
        }


        // Removes any object to the right of right-most "/" part of hte path
        // If the far right part of the path is a "/" the string is not changed
        // Ex:  Before /tmp/obj/test    =>  After /tmp/obj/
        //      Before /tmo/obj/test/   =>  After /tmp/obj/test/
        virtual void removeExistingKey()
        {
          //Remove any existing key from the pointer
          unsigned int lastDelimPos = m_ptrPath.rfind("/");
          if ( ( lastDelimPos != std::string::npos ) &&
               ( lastDelimPos < ( m_ptrPath.size() - 1 ) )
             )
          {
            m_ptrPath.erase( (lastDelimPos + 1), std::string::npos );
          }
          AIS_LOG_DEBUG("REMOVEEXISTINGKEY: %s", m_ptrPath.c_str());
        }

        virtual bool Key(const std::string& key)
        {
          //Remove any existing key from the pointer
          removeExistingKey();
          //And add the new key
          m_ptrPath += key;
          AIS_LOG_DEBUG("KEY: %s", m_ptrPath.c_str());
          return updatePtr();
        }

        virtual void StartObject()
        {
          m_ptrPath += "/";
          AIS_LOG_DEBUG("StartObject: %s", m_ptrPath.c_str());
        }

        virtual void EndObject()
        {
          //Remove any key that may be lingering
          //Takes path from /here/to  =>  /here/
          removeExistingKey();
          //Now remove the last "/" of the path to take us back a level, since removeExistingKey()
          //Is guaranteed to end the path with "/" we can simply remove the last character
          if ( m_ptrPath.size() > 1 )
          {
            m_ptrPath.erase(m_ptrPath.end() - 1);
          }


          AIS_LOG_DEBUG("EndObject: %s", m_ptrPath.c_str());
        }

        virtual void IndexArray(const unsigned int& indx)
        {
          //The index of the array is basically treated like a key
          //ex:  /path/to/array/0 will be the first element of array path
          std::ostringstream stm;
          stm << indx ;
          Key(stm.str());
          AIS_LOG_DEBUG("IndexArray: %s", m_ptrPath.c_str());
        }

        virtual void StartArray()
        {
          //Need to set array capacity before we add the "/" in StartObject
          m_inArray = true;
          m_arraySize = m_pCurrentVal->Capacity();

          //We index an array like an object, so start the object
          StartObject();
          AIS_LOG_DEBUG("StartArray: %s, capacity is %d", m_ptrPath.c_str(), m_arraySize);
        }

        virtual void EndArray()
        {
          m_inArray = false;
          EndObject();
          AIS_LOG_DEBUG("EndArray: %s", m_ptrPath.c_str());
        }

        virtual std::string getPath() const { return m_ptrPath; }

      protected:
        bool updatePtr()
        {
          rapidjson::Pointer myPtr(m_ptrPath.c_str());
          rapidjson::StringBuffer sb;
          myPtr.Stringify(sb);
          AIS_LOG_DEBUG("UpdatePointer:  isValid=%d, sb=%s", myPtr.IsValid(), sb.GetString() );
          m_pCurrentVal = myPtr.Get(m_doc);
          return (m_pCurrentVal != NULL);
        }

        rapidjson::Document&        m_doc;
        std::string                 m_ptrPath;
        rapidjson::Value*           m_pCurrentVal;
        bool                        m_inArray;
        std::size_t                 m_arraySize;

    };
    

    class JsonReader: public JsonReadPtr
    {
      public:
        JsonReader ( const std::string& in ):
          JsonReadPtr( m_doc ),
          m_doc()
        {
          jhm2::json::JsonStringStream inBuf( in );
          m_doc.ParseStream( inBuf );
        }
        virtual ~JsonReader () {}

      private:
        rapidjson::Document m_doc;


    };
  
  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONREADER_H_ */
