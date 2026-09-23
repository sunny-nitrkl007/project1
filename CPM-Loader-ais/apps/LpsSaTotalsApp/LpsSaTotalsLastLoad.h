#ifndef LPSSATOTALSLASTLOAD_H
#define LPSSATOTALSLASTLOAD_H

#include <cstdint>
#include <string>
#include <type_traits>
#include <chrono>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>

#include <boost_helpers/boost_serialization_chrono.hpp>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

#include "LpsSaTotalsPrinterInfo.h"

struct LpsSaTotalsLastLoad {
public:
    bool isSet;
    LpsSaLoadRecordChannelStorage loadRecord;
    uint32_t ticketNumber;

    LpsSaTotalsLastLoad() :
        isSet(false),
        loadRecord(),
        ticketNumber(0) {}

    inline void set(const LpsSaLoadRecordChannel& loadRecord_) {
        loadRecord = loadRecord_;
        ticketNumber = loadRecord_.ticketNumber();
        isSet = true;
    }

    inline void reset() {
        *this = LpsSaTotalsLastLoad();
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    bool print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const;

    void toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr) const;

private:
    std::string applyStringSubstitutions(const std::string& templateStr, const LpsSaLoadRecordSubtotal& subtotal) const;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & isSet;
        ar & loadRecord;
        ar & ticketNumber;

        // If we are de-serializing an old load record, the ticket number didn't exist there.
        // If we are serializing, this should be harmless.
        loadRecord.ticketNumber(ticketNumber);
    }

    friend std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLastLoad& o);
};

BOOST_CLASS_VERSION(LpsSaTotalsLastLoad, 0);

#endif
