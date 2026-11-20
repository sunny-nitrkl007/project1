#include <boost/filesystem.hpp>

#include "FileUpload.hpp"

static boost::filesystem::path destination("/tmp/appdata/CPM/LpsSaListMgrApp/inbox/truck_list.csv");

int main() {

    if (!FileUpload::makeUploadDirectory()) {
        return -1;
    }

    int rVal;

    try {
        // Construction of this object loads the CGI environment.
        FileUpload uploadHandler("");

        if (uploadHandler.copyUpload(destination)) {
            rVal = uploadHandler.respondOk("File copied to list manager inbox.");
        }
        else {
            rVal = uploadHandler.respondError("Unable to copy file to list manager inbox.");
        }

        uploadHandler.removeUploads();
    }
    catch (...) {
        rVal = -1;
    }

    return rVal;
}
