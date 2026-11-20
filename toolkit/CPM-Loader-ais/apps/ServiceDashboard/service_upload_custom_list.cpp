#include <boost/filesystem.hpp>

#include "FileUpload.hpp"

static boost::filesystem::path destination1("/tmp/appdata/CPM/LpsSaListMgrApp/inbox/custom_list_1.csv");
static boost::filesystem::path destination2("/tmp/appdata/CPM/LpsSaListMgrApp/inbox/custom_list_2.csv");
static boost::filesystem::path destination3("/tmp/appdata/CPM/LpsSaListMgrApp/inbox/custom_list_3.csv");
static boost::filesystem::path destination4("/tmp/appdata/CPM/LpsSaListMgrApp/inbox/custom_list_4.csv");

int main() {

    if (!FileUpload::makeUploadDirectory()) {
        return -1;
    }

    int rVal;

    try {
        bool success;
        std::string msg;

        // Construction of this object loads the CGI environment.
        FileUpload uploadHandler("");

        std::string uploadName(uploadHandler.uploadName());

        if (uploadName == "custom-list-1") {
            success = uploadHandler.copyUpload(destination1);
            if (success) {
                msg = "custom-list-1 file copied to list manager inbox.";
            }
            else {
                msg = "Unable to copy custom-list-1 file to list manager inbox.";
            }
        }
        else if (uploadName == "custom-list-2") {
            success = uploadHandler.copyUpload(destination2);
            if (success) {
                msg = "custom-list-2 file copied to list manager inbox.";
            }
            else {
                msg = "Unable to copy custom-list-2 file to list manager inbox.";
            }
        }
        else if (uploadName == "custom-list-3") {
            success = uploadHandler.copyUpload(destination3);
            if (success) {
                msg = "custom-list-3 file copied to list manager inbox.";
            }
            else {
                msg = "Unable to copy custom-list-3 file to list manager inbox.";
            }
        }
        else if (uploadName == "custom-list-4") {
            success = uploadHandler.copyUpload(destination4);
            if (success) {
                msg = "custom-list-4 file copied to list manager inbox.";
            }
            else {
                msg = "Unable to copy custom-list-4 file to list manager inbox.";
            }
        }
        else {
            success = false;
            msg = uploadName + " not supported.";
        }

        if (success) {
            rVal = uploadHandler.respondOk(msg);
        }
        else {
            rVal = uploadHandler.respondError(msg);
        }

        uploadHandler.removeUploads();
    }
    catch (...) {
        rVal = -1;
    }

    return rVal;
}
