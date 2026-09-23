#ifndef LPSSATOTALSOPERATORID_H
#define LPSSATOTALSOPERATORID_H

#include <array>
#include <vector>

#include <boost/filesystem.hpp>

#include <interfaces/DataLinkData/DataLinkData.h>
#include <interfaces/DataLinkData/VarLengthDataLinkParamPool.h>
#include <interfaces/DataLinkData/SecuritySystemCurrentSecurityIDParam.h>


class LpsSaTotalsOperatorId {
public:
    LpsSaTotalsOperatorId() :
        isSet_(false),
        id_(),
        description_() {}

    template<std::size_t SIZE>
    bool update(const std::array<uint8_t, SIZE>& id, const std::string& description) {
        return update(id.data(), id.size(), description);
    }

    bool update(const std::vector<uint8_t>& id, const std::string& description) {
        return update(id.data(), id.size(), description);
    }

    const std::vector<uint8_t>& getId() const {
        return id_;
    }

    const std::string& getDescription() const {
        return description_;
    }

    bool updateWithDataLinkData(const DataLinkData& dataLinkData) {
            const DataLinkParam* pParam;

            // Look for Operator Id
            if (dataLinkData.GetParam(pParam,
                    SecuritySystemCurrentSecurityIDParam::CatExtId,
                    DataLinkParam::DlpParamIdentifierType_t::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT)) {
                const DataLinkParam& param = *pParam;
                if ((VarLengthDataLinkParamPool::CAT_EXT == param.GetVarLengthParamType()) &&
                        (0 == param.GetVarLengthParamDsi()) &&
                        (param.GetVarParamBlockLength() >= SecuritySystemCurrentSecurityIDParam::m_DataLengthMinSize)) {
                    // Unfortunately, we have to cast away the const here because we don't have
                    // a read-only version of the SecuritySystemCurrentSecurityIDParam class
                    const SecuritySystemCurrentSecurityIDParam idParam(const_cast<DataLinkParam&>(param));
                    std::vector<uint8_t> id;
                    std::string description;
                    if (idParam.getID(id) && idParam.getIDDescription(description)) {
                        // We got data.
                        return update(id, description);
                    }
                }
            }

            return false; // nothing changed
        }

private:
    bool update(const uint8_t* id, std::size_t idSize, const std::string& description) {
        bool changed = false;

        if (idSize != id_.size()) {
            id_.resize(idSize);
            changed = true;
        }

        for (std::size_t idx = 0; idx < idSize; ++idx) {
            if (id[idx] != id_[idx]) {
                id_[idx] = id[idx];
                changed = true;
            }
        }

        if (description != description_) {
            description_ = description;
            changed = true;
        }

        if (!isSet_) {
            isSet_ = true;
            changed = true;
        }

        return changed;
    }

    bool isSet_;
    std::vector<uint8_t> id_;
    std::string description_;
};

#endif
