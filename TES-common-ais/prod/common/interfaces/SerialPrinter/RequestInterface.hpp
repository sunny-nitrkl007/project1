#ifndef SERIALPRINTER_REQUESTINTERFACE_HPP
#define SERIALPRINTER_REQUESTINTERFACE_HPP

#include <cstdint>
#include <type_traits>
#include <string>

#include <ais/serialization/Datum.h>
#include <ais/serialization/csvable.h>

enum class SerialPrinterRequestInterfaceCommand : uint8_t {
    PRINT,
    TEST
};

#define SerialPrinterRequestInterfaceCommand_Base_t(val) (static_cast<typename std::underlying_type<SerialPrinterRequestInterfaceCommand>::type>(val))

/*
 * The interface storage class.
 */
class SerialPrinterRequestInterfaceStorage : public csvable {
public:
    SerialPrinterRequestInterfaceStorage() = default;

    SerialPrinterRequestInterfaceCommand command;
    std::string arg1;
    uint8_t arg2;

    inline const std::string& filePath() const { return arg1; }
    inline void filePath(const std::string& name) { arg1 = name; }

    inline uint8_t numberOfCopies() const { return (arg2 >= 3) ? 3 : arg2; }
    inline void numberOfCopies(uint8_t copies) { arg2 = copies; }

    void toCsv(CsvOutStream& out) const {
        out("Command", SerialPrinterRequestInterfaceCommand_Base_t(command));
        out("Arg 1", arg1);
        out("Arg 2", arg2);
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & command;
        ar & arg1;
        ar & arg2;
    }
};

/*
 * Datum template specialization.
 *   Defines a new specialization of the Datum class
 *   derived from the base 'storage' class.
 */
typedef Datum<SerialPrinterRequestInterfaceStorage> SerialPrinterRequestInterface;

BOOST_CLASS_VERSION(SerialPrinterRequestInterfaceStorage, 1);

#endif /* SERIALPRINTER_REQUESTINTERFACE_HPP */
