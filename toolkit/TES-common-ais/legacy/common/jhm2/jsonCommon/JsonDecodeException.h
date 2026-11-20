///////////////////////////////////////////////////////////////////////////////
/// @file      JsonDecodeException.h
/// @author    strubjc
/// @date      Apr 6, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONDECODEEXCEPTION_H_
#define JSONDECODEEXCEPTION_H_

#include <exception>
#include <string>

namespace jhm2
{
  namespace json
  {
    
    class JsonDecodeException: public std::exception
    {
      public:
        JsonDecodeException () throw() {}
        JsonDecodeException (const std::string &path) throw(): m_err("Error Decoding Path: " + path) {}
        JsonDecodeException (const std::string &err, const std::string &path) throw(): m_err( err + ": " + path ) {}
        ~JsonDecodeException () throw() {}

        virtual const char* what() const throw()
        {
          return this->m_err.c_str();
        }

      private:
        std::string m_err;
    };
  
  } /* namespace json */
} /* namespace jhm2 */

#endif /* JSONDECODEEXCEPTION_H_ */
