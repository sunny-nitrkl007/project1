#ifndef VP3RECORDTYPECONTAINER_H
#define VP3RECORDTYPECONTAINER_H

#include <interfaces/VP3Record/VP3Record.h>

class VP3RecordTypeContainer
{
public:

    VP3RecordTypeContainer(
            int recordType,
            const std::string& uid64,
            unsigned short sizeOfRecord,
            const std::string& rBlockData,
            unsigned short numberOfUIDs) :
        recordType_(recordType),
        uid64_(uid64),
        numberOfUIDs_(numberOfUIDs),
        sizeOfRecord_(sizeOfRecord),
        numberOfRecords_(1),
        rBlockData_(rBlockData) {}

    VP3RecordTypeContainer(const VP3RecordStorage& vp3Record) :
        VP3RecordTypeContainer(vp3Record.getRecordType(),
                vp3Record.getUIDList(),
                vp3Record.getSizeOfRecord(),
                vp3Record.getRBlockData(),
                vp3Record.getNumberOfUIDs()) {}

    int getRecordType() const {
    	return recordType_;
    }

    const std::string& getUID64() const {
    	return uid64_;
    }

    bool equalUIDs(const std::string& uid64) const {
    	if (uid64_.compare(uid64) == 0) {
    		return true;
    	}
    	else {
    	    return false;
    	}
    }

    int getSizeOfRecord() const {
    	return sizeOfRecord_;
    }

    int getNumberOfUIDs() const {
        return numberOfUIDs_;
    }

    int getNumberOfRecords() const {
    	return numberOfRecords_;
    }

    const std::string& getRBlockData() const {
    	return rBlockData_;
    }

    bool addRBlockData(const std::string& rBlockData) {
        rBlockData_ += rBlockData;
        numberOfRecords_++;
    	return true;
    }

private:
    int recordType_;
    std::string uid64_;
    unsigned short numberOfUIDs_;
    unsigned short sizeOfRecord_;
    unsigned short numberOfRecords_;
    std::string rBlockData_;
};

#endif
