////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: VarLengthDataLinkParamPool
//
// File Name: VarLengthDataLinkParamPool.h
//
//  Abstract: Provide a pool of objects of types derived from class VarLengthDataLinkParam
//            such that a specific object can be retrieved by an enum value that denotes it.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef VARLENGTHDATALINKPARAMFACTORY_DECL_H
#define VARLENGTHDATALINKPARAMFACTORY_DECL_H

#include <boost/smart_ptr/make_shared.hpp>
#include <cstdint>
#include <unordered_map>

class DataLinkParam;
class VarLengthDataLinkParam;

namespace VarLengthDataLinkParamFactory
{
    // VarLengthParamType values are used to reference entries in the m_VarLengthPool.
    enum VarLengthParamType {
        NOT_APPLICABLE,
        GPS,
        SPL_PID_REV_DATA_BYTE_ORDER, // use this for special pid's to reverse data (ex pid:F5D9)
        TIME_ZONE,
        PRODUCT_ID,
        PGN, // Use for Public PGN Data
        SPN,

        /*
         * The following is just a special case of Cat Extension Id (CAT_EXT)
         * It needs to be kept here so that bmi_autogen_typedef_values.csv doesn't need to change
         * and configs can be backwards compatible.
         */
        do_not_use_SECURITY_SYSTEM_CURRENT_KEY,

        UNSUPPORTED,
        CAT_EXT
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Provide string representation of VarLengthParamType
    ///
    /// @param VarLengthParamType
    ///
    /// @return VarLengthParamType converted to string
    ///
    ///////////////////////////////////////////////////////////////////////////////
    inline std::string GetVarLengthParamTypeString(VarLengthParamType type)
    {
        const std::unordered_map<uint16_t, const char*> EnumStrings {
            { NOT_APPLICABLE,                 "NOT_APPLICABLE" },
            { GPS,                            "GPS" },
            { SPL_PID_REV_DATA_BYTE_ORDER,    "SPL_PID_REV_DATA_BYTE_ORDER" },
            { TIME_ZONE,                      "TIME_ZONE" },
            { PRODUCT_ID,                     "PRODUCT_ID" },
            { PGN,                            "PGN" },
            { SPN,                            "SPN" },
            { UNSUPPORTED,                    "UNSUPPORTED" },
            { CAT_EXT,                        "CAT_EXT" }
        };
        auto   it  = EnumStrings.find(static_cast<uint16_t>(type));
        return it == EnumStrings.end() ? "--" : it->second;
    }

    inline boost::shared_ptr<VarLengthDataLinkParam> GetNewParam(DataLinkParam& param);
};

#endif // VARLENGTHDATALINKPARAMFACTORY_DECL_H

