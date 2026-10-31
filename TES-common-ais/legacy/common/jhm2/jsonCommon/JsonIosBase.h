///////////////////////////////////////////////////////////////////////////////
/// @file      JsonIosBase.h
/// @author    strubjc
/// @date      Apr 11, 2016
/// @brief     Base Class for Json Input/Output Routines
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JSONIOSBASE_H_
#define JSONIOSBASE_H_

//The Json Ios module has a very bad dependency loop
//So any module needing access to the JsonIosAbstractBase
//Should include this file instead

//This forces the compiler to load the JsonInStream and JsonOutStream
//First, which include the JsonIosAbstractBase header, then finally force
//Inclusion of the AbstractBase Inline Last (and only once)

#include "JsonInStream.h"
#include "JsonOutStream.h"
#include "JosnIosAbstractBase_inl.h"


#endif /* JSONIOSBASE_H_ */
