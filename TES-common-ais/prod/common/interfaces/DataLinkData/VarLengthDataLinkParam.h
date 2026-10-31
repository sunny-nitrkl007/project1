#ifndef VARLENGTHDATALINKPARAM_H
#define VARLENGTHDATALINKPARAM_H

#include "VarLengthDataLinkParam_decl.h"
#include "DataLinkParam.h"

inline VarLengthDataLinkParam::VarLengthDataLinkParam(
            VarLengthParamBlock_t& paramValue) :
            m_ParamValue(paramValue) {}

inline VarLengthDataLinkParam::VarLengthDataLinkParam(DataLinkParam& param) :
    m_ParamValue(param.LastGoodValue) {}

#endif // VARLENGTHDATALINKPARAM_H
