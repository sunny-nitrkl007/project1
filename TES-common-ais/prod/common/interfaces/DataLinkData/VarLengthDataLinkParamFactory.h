#ifndef VARLENGTHDATALINKPARAMFACTORY_H
#define VARLENGTHDATALINKPARAMFACTORY_H

#include "VarLengthDataLinkParamFactory_decl.h"
#include "GPSDataLinkParam.h"
#include "TimeZoneDataLinkParam.h"
#include "ProductIdDataLinkParam.h"
#include "SecuritySystemCurrentKeyParam.h"
#include "SecuritySystemCurrentSecurityIDParam.h"
#include "VarLengthDataLinkParam.h"
#include "DataLinkParam.h"

namespace VarLengthDataLinkParamFactory
{

inline boost::shared_ptr<VarLengthDataLinkParam> GetNewParam(
        DataLinkParam& param) {

    boost::shared_ptr<VarLengthDataLinkParam> result = nullptr;
    const VarLengthParamType paramType = param.GetVarLengthParamType();
    switch (paramType) {
    case (GPS): {
        result = boost::make_shared<GPSDataLinkParam>(param);
        break;
    }
    case (TIME_ZONE): {
        result = boost::make_shared<TimeZoneDataLinkParam>(param);
        break;
    }
    case (PRODUCT_ID): {
        result = boost::make_shared<ProductIdDataLinkParam>(param);
        break;
    }
    case (UNSUPPORTED): {
        result = boost::make_shared<VarLengthDataLinkParam>(param);
        break;
    }
    case (PGN):
    case (SPN):
    case (SPL_PID_REV_DATA_BYTE_ORDER):
    case (NOT_APPLICABLE):
    default: {
        break;
    }
    }

    return result;
}

}

#endif // VARLENGTHDATALINKPARAMFACTORY_H

