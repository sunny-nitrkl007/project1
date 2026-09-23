#ifndef FILEUPLOAD_HPP
#define FILEUPLOAD_HPP

#include <string>
#include <ostream>

#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>

// Due to boost/cgi bug we need to keep file uploads and clean up ourselves.
// - https://github.com/darrengarvey/cgi/issues/19
// The bug basically deletes the uploads before the application can access them.
#define BOOST_CGI_KEEP_FILE_UPLOADS
//#undef BOOST_CGI_NO_BOOST_FILESYSTEM

#ifndef BOOST_CGI_UPLOAD_DIRECTORY
#   define BOOST_CGI_UPLOAD_DIRECTORY "/tmp/appdata/CPM/ServiceDashboard/uploads/"
#endif

// Make sure to include semicolon as an unsafe filename character
#define BOOST_CGI_UNSAFE_FILENAME_CHARS "`*\"\'\0<>;:~.|/\\"

#include <boost/cgi/cgi.hpp>

class FileUpload {
public:
    FileUpload() : FileUpload("") {}

    FileUpload(const std::string& uploadName) :
            uploadName_(uploadName.c_str()),
            request_(), // This loads the CGI environment
            filePath_() {

        if (uploadName_.empty()) {
            // Find the last file upload and use that.  All other uploads are ignored
            for (auto it = request_.uploads.rbegin(); it != request_.uploads.rend(); ++it) {
                const boost::cgi::common::form_part& part = it->second;
                if (!part.path.empty()) {
                    uploadName_ = it->first;
                    filePath_ = part.path;
                }
            }
        }
        else if (request_.uploads.exists(uploadName_)) {
            const boost::cgi::common::form_part& part = request_.uploads[uploadName_];
            if (!part.path.empty()) {
                filePath_ = part.path;
            }
        }
    }

    static bool makeUploadDirectory() {
        bool success = true;
        boost::filesystem::path p(BOOST_CGI_UPLOAD_DIRECTORY);
        try {
            boost::filesystem::file_status fs = boost::filesystem::status(p);
            if (!boost::filesystem::exists(fs)) {
                // will throw if directory cannot be made.
                boost::filesystem::create_directories(p);
            }
            else if (!boost::filesystem::is_directory(fs)) {
                // path exists and it is not a directory!
                success = false;
            }
            else {
                // path exists and it is a directory.
            }
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    inline const char* uploadName() {
        return uploadName_.c_str();
    }

    inline const boost::filesystem::path& filePath() {
        return filePath_;
    }

    bool fileExists() {
        boost::system::error_code ec;
        if (boost::filesystem::is_regular_file(filePath_, ec)) {
            return true;
        }
        return false;
    }

    bool copyUpload(const boost::filesystem::path& destination) {
        bool success = true;

        try {
            // Copy file to destination
            boost::filesystem::copy_file(filePath_, destination);
        }
        catch (...) {
            success = false;
        }

        return success;
    }

    uint32_t removeUploads() {
        uint32_t numRemoved = 0;
        boost::system::error_code ec;
        for (auto it = request_.uploads.begin(); it != request_.uploads.end(); ++it) {
            const boost::cgi::common::form_part& part = it->second;
            const boost::filesystem::path& path = part.path;
            if (boost::filesystem::is_regular_file(path, ec)) {
                if (boost::filesystem::remove(path, ec)) {
                    if (!ec) {
                        ++numRemoved;
                    }
                }
            }
        }
        return numRemoved;
    }

    int respondNoContent() {
        boost::cgi::response response;
        response.status(boost::cgi::common::http::status_code::no_content);
        return boost::cgi::commit(request_, response);
    }

    int respondOk(const std::string& message = "") {
        if (message.empty()) {
            return respondNoContent();
        }
        else {
            boost::cgi::response response;
            response.status(boost::cgi::common::http::status_code::ok);
            response.set(boost::cgi::content_type("text/plain"));
            response.write(message);
            return boost::cgi::commit(request_, response);
        }
    }

    int respondError(const std::string& message = "") {
        boost::cgi::response response;
        response.status(boost::cgi::common::http::status_code::internal_server_error);
        response.set(boost::cgi::content_type("text/plain"));
        response.write(message);
        return boost::cgi::commit(request_, response, -1);
    }

private:
    boost::cgi::common::name uploadName_; // Case insensitive string
    boost::cgi::request request_;
    boost::filesystem::path filePath_;
};

#endif
