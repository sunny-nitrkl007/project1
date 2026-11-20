///////////////////////////////////////////////////////////////////////////////
/// @file      JsonStreamBuf.h
/// @author    strubjc
/// @date      Dec 15, 2015
/// @brief     Wrapper type for RapidJson StringBuffer
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONSTREAMBUF_H_
#define JSONSTREAMBUF_H_

#include <rapidjson/stringbuffer.h>

namespace jhm2
{
  namespace json
  {
    
    class JsonStreamBuf: public rapidjson::StringBuffer
    {
      public:
        JsonStreamBuf () {}
        virtual ~JsonStreamBuf () {}
    };
  
  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONSTREAMBUF_H_ */
