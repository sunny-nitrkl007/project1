////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: VarLengthDataLinkParam
//
// File Name: VarLengthDataLinkParam.h
//
//  Abstract: Base class that contains a sequence of data link bytes.
//            Derived classes extend this class with methods to parse data fields from
//            the byte sequence.
//            This class is a helper to class DataLinkParam
//
////////////////////////////////////////////////////////
#ifndef VARLENGTHDATALINKPARAM_DECL_H
#define VARLENGTHDATALINKPARAM_DECL_H

#include <stdint.h>
#include <vector>

class DataLinkParam;

class VarLengthDataLinkParam
{
public:
    typedef std::vector<uint8_t> VarLengthParamBlock_t;

    inline VarLengthDataLinkParam(VarLengthParamBlock_t& paramValue);

    inline VarLengthDataLinkParam(DataLinkParam& param);

    virtual ~VarLengthDataLinkParam() {}

    // Size is always ok by default
    virtual inline bool isSizeOk() const { return true; }

protected:
    VarLengthParamBlock_t& m_ParamValue;
};

#endif // VARLENGTHDATALINKPARAM_DECL_H
