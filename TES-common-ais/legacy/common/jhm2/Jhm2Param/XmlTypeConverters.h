///////////////////////////////////////////////////////////////////////////////
/// @file      XmlTypeConverters.h
/// @author    strubjc
/// @date      Mar 21, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef XMLTYPECONVERTERS_H_
#define XMLTYPECONVERTERS_H_

#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


class XmlTypeConverters
{
  public:

    template <class T>
    static std::string toXmlStr( const T& in )
    {
      return boost::lexical_cast<std::string>(in);
    }

    static std::string toXmlStr( const double& in )
    {
      std::stringstream ss;
      ss.setf ( std::ios::fixed, std::ios::floatfield );
      ss.precision( 2 );
      ss << in;
      return ss.str();
    }

    static std::string toXmlStr( const char& in )
    {
      int tmpIn = static_cast<int>(in);
      return toXmlStr(tmpIn);
    }

    static std::string toXmlStr( const unsigned char& in )
    {
      unsigned int tmpIn = static_cast<unsigned int>(in);
      return toXmlStr(tmpIn);
    }

    static std::string toXmlStr( const float& in )
    {
      std::stringstream ss;
      ss.setf ( std::ios::fixed, std::ios::floatfield );
      ss.precision( 2 );
      ss << in;
      return ss.str();
    }

    static std::string toXmlStr( const std::string& str )
    {
      std::string outStr = str;
      boost::replace_all(outStr, ">", "&gt;");
      boost::replace_all(outStr, "<", "&lt;");
      boost::replace_all(outStr, "&", "&amp;");
      boost::replace_all(outStr, "%", "&#37;");
      return outStr;
    }

  private:
    XmlTypeConverters();  //To Prevent Use
    ~XmlTypeConverters();

};


#endif /* XMLTYPECONVERTERS_H_ */
