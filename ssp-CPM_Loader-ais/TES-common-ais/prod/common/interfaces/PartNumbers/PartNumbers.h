#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/interfaces/traits/csvable.h>
#include <std_types.h>
#include <algorithm>
#include <iostream>
//#include <cctype>


#ifndef _PartNumbers_h_
#define _PartNumbers_h_

class PartNumbersStorage : public csvable
{
public:
    static bool IsProductIdValid(const std::string& id) {
        if (id.size() < 8) {
            return false;
        }

        return isalnum(id[0]) && isalnum(id[1]) && isalnum(id[2]) && isdigit(id[3]) &&
                isdigit(id[4]) && isdigit(id[5]) && isdigit(id[6]) && isdigit(id[7]);
    }

    bool IsProductIdValid() const {
        return (IsProductIdNumSet() && IsProductIdValid(productIdNum));
    }

    // Returns true if the ProductIdNum is set, false otherwise
    bool IsProductIdNumSet() const { return productIdNumSet; }

    // Returns true if the SwGroupPartNum is set, false otherwise
    bool IsSwGroupPartNumSet() const { return swGroupPartNumSet; }

    // Returns true if the SwGroupReleaseDate is set, false otherwise
    bool IsSwGroupReleaseDateSet() const { return swGroupReleaseDateSet; }

    // Returns true if the SwGroupDescription is set, false otherwise
    bool IsSwGroupDescriptionSet() const { return swGroupDescriptionSet; }

    // Returns true if the ECMPartNum is set, false otherwise
    bool IsECMPartNumSet() const { return ecmPartNumSet; }

    // Returns true if the ModelNum is set, false otherwise
    bool IsModelNumSet() const { return modelNumSet; }

    // Returns true if the SerialNum is set, false otherwise
    bool IsECMSerialNumSet() const { return ecmSerialNumSet; }

    // Returns true if the Equipment ID is set, false otherwise
    bool IsEquipmentIdSet() const { return equipmentIdSet; }

    // Stores the ProductIdNum
    void SetProductIdNum(const std::string& ProductIdNum) { productIdNum = ProductIdNum; productIdNumSet = true; }

    // Stores the ProductIdNum
    void SetEquipmentId(const std::string& EquipmentId) { equipmentId = EquipmentId; equipmentIdSet = true; }

    // Stores the SwGroupPartNum
    void SetSwGroupPartNum(const std::string& SwGroupPartNum) { swGroupPartNum = SwGroupPartNum; swGroupPartNumSet = true; }

    // Stores the SwGroupReleaseDate
    void SetSwGroupReleaseDate(const std::string& SwGroupReleaseDate) { swGroupReleaseDate = SwGroupReleaseDate; swGroupReleaseDateSet = true; }

    // Stores the SwGroupDescription
    void SetSwGroupDescription(const std::string& SwGroupDescription) { swGroupDescription = SwGroupDescription; swGroupDescriptionSet = true; }

    // Stores the ECMPartNum
    void SetECMPartNum(const std::string& ECMPartNum) { ecmPartNum = ECMPartNum; ecmPartNumSet = true; }

    // Stores the ModelNum
    void SetModelNum(const std::string& ModelNum) { modelNum = ModelNum; modelNumSet = true; }

    // Stores the SerialNum
    void SetECMSerialNumber(const std::string& ECMSerialNum) { ecmSerialNum = ECMSerialNum; ecmSerialNumSet = true; }

    // Returns the ProductIdNum
    std::string GetProductIdNum() const { return productIdNum; }

    // Returns the EquipmentId
    std::string GetEquipmentId() const { return equipmentId; }

    // Returns the SwGroupPartNum
    std::string GetSwGroupPartNum() const { return swGroupPartNum; }

    // Returns the SwGroupReleaseDate
    std::string GetSwGroupReleaseDate() const { return swGroupReleaseDate; }

    // Returns the SwGroupDescription
    std::string GetSwGroupDescription() const { return swGroupDescription; }

    // Returns the ECMPartNum
    std::string GetECMPartNum() const { return ecmPartNum; }

    // Returns the ModelNum
    std::string GetModelNum() const { return modelNum; }

    // Returns the SerialNum
    std::string GetECMSerialNum() const { return ecmSerialNum; }

    PartNumbersStorage() : productIdNum(""),
            equipmentId(""),
            swGroupPartNum(""),
            swGroupReleaseDate(""),
            swGroupDescription(""),
            ecmPartNum(""),
            modelNum(""),
            ecmSerialNum(""),
            productIdNumSet(false),
            swGroupPartNumSet(false),
            swGroupReleaseDateSet(false),
            swGroupDescriptionSet(false),
            ecmPartNumSet(false),
            modelNumSet(false),
            ecmSerialNumSet(false),
            equipmentIdSet(false) {}

    template <class Archive>
    void serialize(Archive &ar, unsigned int version) {
        ar & productIdNum;
        ar & productIdNumSet;
        ar & swGroupPartNum;
        ar & swGroupPartNumSet;
        ar & swGroupReleaseDate;
        ar & swGroupReleaseDateSet;
        ar & swGroupDescription;
        ar & swGroupDescriptionSet;
        ar & ecmPartNum;
        ar & ecmPartNumSet;
        ar & modelNum;
        ar & modelNumSet;
        ar & ecmSerialNum;
        ar & ecmSerialNumSet;
        ar & equipmentId;
        ar & equipmentIdSet;
    }

    /////////////////////////////////////////////////////////////////////////////
    /// @brief Print structure out in CSV format
    /// @param out - output stream
    /////////////////////////////////////////////////////////////////////////////
    void toCsv(CsvOutStream &out) const {
        out("ProductIdNum", productIdNum);
        out("ProductIdNumSet", productIdNumSet);
        out("SwGroupPartNum", swGroupPartNum);
        out("SwGroupPartNumSet", swGroupPartNumSet);
        out("SwGroupReleaseDate", swGroupReleaseDate);
        out("SwGroupReleaseDateSet", swGroupReleaseDateSet);
        out("SwGroupDescription", swGroupDescription);
        out("SwGroupDescriptionSet", swGroupDescriptionSet);
        out("ECMPartNum", ecmPartNum);
        out("ECMPartNumSet", ecmPartNumSet);
        out("ModelNum", modelNum);
        out("ModelNumSet", modelNumSet);
        out("ECMSerialNum", ecmSerialNum);
        out("ECMSerialNumSet", ecmSerialNumSet);
        out("EquipmentId", equipmentId);
        out("EquipmentIdSet", equipmentIdSet);
    }

private:
    /* Add Fields Here */
    std::string productIdNum;
    std::string equipmentId;
    std::string swGroupPartNum;
    std::string swGroupReleaseDate;
    std::string swGroupDescription;
    std::string ecmPartNum;
    std::string modelNum;
    std::string ecmSerialNum;

    bool productIdNumSet;
    bool swGroupPartNumSet;
    bool swGroupReleaseDateSet;
    bool swGroupDescriptionSet;
    bool ecmPartNumSet;
    bool modelNumSet;
    bool ecmSerialNumSet;
    bool equipmentIdSet;

    static inline bool isalpha(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
    static inline bool isdigit(char c) { return (c >= '0' && c <= '9'); }
    static inline bool isalnum(char c) { return (isalpha(c) || isdigit(c)); }
};

typedef Datum<PartNumbersStorage> PartNumbers;

BOOST_CLASS_VERSION(PartNumbersStorage, 1);
#endif
