///////////////////////////////////////////////////////////////////////////////
/// @file      JsonStringStream.h
/// @author    strubjc
/// @date      Apr 6, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONSTRINGSTREAM_H_
#define JSONSTRINGSTREAM_H_

#include <rapidjson/rapidjson.h>

namespace jhm2
{
  namespace json
  {
    
    class JsonStringStream: public rapidjson::StringStream
    {
      public:
        JsonStringStream (const std::string& in):
          rapidjson::StringStream( in.c_str() ) {}
        virtual ~JsonStringStream () {}
    };
  
  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONSTRINGSTREAM_H_ */
