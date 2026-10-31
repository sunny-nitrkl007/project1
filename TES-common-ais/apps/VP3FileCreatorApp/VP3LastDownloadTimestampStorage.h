////////////////////////////////////////////////////////////////////////
// Function        : LastDownloadTimestampStorage
// Description     : Structure to store the Last Download timestamp to nvm and read at init
//
// Return Type     : None
// Argument [in]   : taskName
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>
#include <boost/filesystem.hpp>


struct LastDownloadTimestampStorage {
public:
    struct Timestamp {
    public:
    	uint32_t UTC;
    	int16_t  Offset;
    	uint32_t SMH;

        inline void reset() {
        	UTC = 0;
        	Offset = 0;
        	SMH = 0;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & UTC;
            ar & Offset;
            ar & SMH;
        }
    };

    Timestamp LastDownloadTimestamp;

    inline void reset() {
    	LastDownloadTimestamp.reset();
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & LastDownloadTimestamp;
    }

    friend std::ostream& operator<<(std::ostream& os, const LastDownloadTimestampStorage& o);
};

