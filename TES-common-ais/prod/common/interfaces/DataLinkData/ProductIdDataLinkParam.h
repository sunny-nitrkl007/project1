////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: ProductIdDataLinkParam
//
// File Name: ProductIdDataLinkParam.h
//
//  Abstract: Parse Product ID data fields from a sequence of data link bytes.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef PRODUCTIDDATALINKPARAM_H
#define PRODUCTIDDATALINKPARAM_H

#include "VarLengthDataLinkParam.h"
#include <cat_std_types.h>
#include <cstring>

class ProductIdDataLinkParam : public VarLengthDataLinkParam
{
   public:
      ProductIdDataLinkParam(DataLinkParam& param) : VarLengthDataLinkParam(param) {}

      ProductIdDataLinkParam(VarLengthParamBlock_t& paramValue) :
                  VarLengthDataLinkParam(paramValue) {}

      ~ProductIdDataLinkParam(){}

      static const unsigned_8 m_ProductIdParamSize = 8;

      inline bool isSizeOk() const {
          return m_ParamValue.size() >= m_ProductIdParamSize;
      }

      char* GetProductId(char Productid[]) const {
          if (isSizeOk()) {
              std::memcpy(Productid, &m_ParamValue[0], m_ProductIdParamSize);
          }
          return Productid;
      }



   private:
	

};
#endif //PRODUCTIDDATALINKPARAM_H

