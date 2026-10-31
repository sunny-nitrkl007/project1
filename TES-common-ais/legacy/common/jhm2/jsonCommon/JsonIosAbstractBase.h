///////////////////////////////////////////////////////////////////////////////
/// @file      JsonIosAbstractBase.h
/// @author    strubjc
/// @date      Apr 14, 2016
/// @brief     Abstract Base for defining JSON input/output functions
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONIOSABSTRACTBASE_H_
#define JSONIOSABSTRACTBASE_H_

#include <util/FlagContainer.h>

class JsonIosAbstractBase
{
  public:

    enum eIosType
    {
      INPUT=0,
      OUTPUT,
    };

    JsonIosAbstractBase(eIosType iosType): m_type( iosType ) {}
    virtual ~JsonIosAbstractBase() {}

    template<class T>
    void operator()(const std::string& key, T& val );


    template<class T>
    void operator()(const std::string& key, T& val, FlagContainer& fc );


  protected:
    eIosType m_type;
};


#endif /* JSONIOSABSTRACTBASE_H_ */
