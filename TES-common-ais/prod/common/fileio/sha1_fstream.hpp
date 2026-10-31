#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <utility>
#include <iomanip>
#include <array>

#include <boost/filesystem.hpp>
#include <boost/uuid/detail/sha1.hpp>

#ifndef SHA1_FSTREAM_HPP
#define SHA1_FSTREAM_HPP

namespace tes_common_ais {

    namespace fs = boost::filesystem;

    inline std::array<char, 20> get_sha1_array(std::istream& is) {
        boost::uuids::detail::sha1 sha1;
        char buffer[100];
        while (is.read(&buffer[0], sizeof(buffer) / sizeof(buffer[0]))) {
            sha1.process_bytes(&buffer[0], static_cast<size_t>(is.gcount()));
        }
        if (is.gcount() > 0) {
            sha1.process_bytes(&buffer[0], static_cast<size_t>(is.gcount()));
        }
        unsigned int hash[5] = {0};
        sha1.get_digest(hash);

        unsigned int hash_swap[5];
        for (int i=0; i<5; i++) {
            hash_swap[i] = (hash[i] & 0x000000ff) << 24 |
                    (((hash[i] & 0x0000ff00) >> 8) << 16) |
                    (((hash[i] & 0x00ff0000) >> 16) << 8) |
                    ((hash[i] & 0xff000000) >> 24);
        }
        std::array <char, 20> ar;
        char* hash_ptr = reinterpret_cast<char*>(hash_swap);
        for (unsigned int i=0; i < sizeof(hash_swap); i++, hash_ptr++) {
            ar[i] = *hash_ptr;
        }
        return ar;
    }

    namespace detail {
        /*
         * The following functions are "inline" in order to:
         * - "allow multiple definitions"
         * - maintain "external linkage".
         *
         * Allowing multiple definitions allows header only implementation.
         *
         * Maintaining external linkage keeps from including a unique, but
         * identical, definition of the function in each translation unit.
         * (unless the compiler decides to truly inline the function)
         */

        template<typename Iter>
        inline std::string make_hex_string(Iter first, Iter last, bool use_uppercase = true) {
            std::ostringstream ss;
            ss << std::hex << std::setfill('0');
            if (use_uppercase)
                ss << std::uppercase;
            while (first != last) {
                ss << std::setw(2) << static_cast<int>(*first);
                first++;
            }
            return ss.str();
        }

        inline std::string get_sha1(std::istream& is) {
            boost::uuids::detail::sha1 sha1;
            char buffer[100];
            while (is.read(&buffer[0], sizeof(buffer) / sizeof(buffer[0]))) {
                sha1.process_bytes(&buffer[0], static_cast<size_t>(is.gcount()));
            }
            if (is.gcount() > 0) {
                sha1.process_bytes(&buffer[0], static_cast<size_t>(is.gcount()));
            }
            unsigned int hash[5] = {0};
            //boost::uuids::detail::sha1::digest_type hash = { 0, 0, 0, 0, 0 };
            sha1.get_digest(hash);
            return make_hex_string(std::begin(hash), std::end(hash), true);
        }

        inline void copy_file(const std::string& from, const std::string& to) {
            std::ifstream ifs(from, std::ios_base::binary);
            std::ofstream ofs(to, std::ios_base::binary);
            ofs << ifs.rdbuf();
            ofs.close();
            ifs.close();
        }
    } // detail

    class sha1_fstream {
    public:
        static bool remove_files(const std::string& filename) {
            bool rval = fs::remove(filename);
            fs::remove(filename + ".sha1");
            fs::remove(filename + ".bak");
            fs::remove(filename + ".bak.sha1");
            return rval;
        }

    protected:
        static bool check_file(const std::string& filename, std::string& sha1) {
            std::string sha1_actual;
            { // Open the file to do the checksum.
                std::ifstream ifs(filename, std::ios_base::binary);
                sha1_actual = detail::get_sha1(ifs);
                ifs.close();
            }

            std::string sha1_check;
            { // Open the file with the answer.
                std::ifstream ifs(filename + ".sha1");
                std::getline(ifs, sha1_check);
                ifs.close();
            }

            if (sha1_actual == sha1_check) {
                sha1 = sha1_actual;
                return true;
            }
            else {
                return false;
            }
        }
    };

    class sha1_ifstream : public std::ifstream, public sha1_fstream {
    public:
        sha1_ifstream(bool two_copy = false) :
            std::ifstream(),
            _twoCopy{ two_copy },
            _primaryNeedsFixing{ false },
            _backupNeedsFixing{ false } {}

        explicit sha1_ifstream(const char* filename, std::ios_base::openmode mode = std::ios_base::in, bool two_copy = false) :
            _twoCopy{ two_copy } {
            open(filename, mode);
        }
        explicit sha1_ifstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in, bool two_copy = false) :
            _twoCopy{ two_copy } {
            open(filename, mode);
        }

        // Get rid of all of the copy and move semantics
        sha1_ifstream(sha1_ifstream&& x) = delete;
        sha1_ifstream(const sha1_ifstream&) = delete;
        sha1_ifstream& operator=(sha1_ifstream&& _Right) = delete;
        void _Assign_rv(sha1_ifstream&& _Right) = delete;
        void swap(sha1_ifstream& _Right) = delete;

        void open(const char* filename, std::ios_base::openmode mode = std::ios_base::in) {
            open(std::string{ filename }, mode);
        }

        void open(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in) {
            std::string sha1;
            if (check_file(filename, sha1)) {
                std::ifstream::open(filename, mode);
                if (_twoCopy) {
                    std::string sha1Bak;
                    if (check_file(filename + ".bak", sha1Bak)) {
                        if (sha1 != sha1Bak) _backupNeedsFixing = true;
                    }
                    else {
                        _backupNeedsFixing = true;
                    }
                }
            }
            else if (_twoCopy) {
                std::string sha1Bak;
                if (check_file(filename + ".bak", sha1Bak)) {
                    std::ifstream::open(filename + ".bak", mode);
                    _primaryNeedsFixing = true;
                }
                else {
                    // None of the files are good.
                    _primaryNeedsFixing = true;
                    _backupNeedsFixing = true;
                    setstate(ios_base::failbit);
                }
            }
            else {
                // None of the files are good.
                _primaryNeedsFixing = true;
                setstate(ios_base::failbit);
            }

            if (*this) _filename = filename;
        }

        bool fix_it() {
            bool fixed = false;
            if (_twoCopy && !_filename.empty()) {
                if (_primaryNeedsFixing) {
                    if (!_backupNeedsFixing) {
                        // Copy backup to primary
                        detail::copy_file(_filename + ".bak", _filename);
                        detail::copy_file(_filename + ".bak.sha1", _filename + ".sha1");
                        _primaryNeedsFixing = false;
                        fixed = true;
                    }
                }
                else if (_backupNeedsFixing) {
                    // Copy primary to backup
                    detail::copy_file(_filename, _filename + ".bak");
                    detail::copy_file(_filename + ".sha1", _filename + ".bak.sha1");
                    _backupNeedsFixing = false;
                    fixed = true;
                }
                else {
                    fixed = true;
                }
            }
            return fixed;
        }

        bool is_corrupt() {
            return (_primaryNeedsFixing || (_twoCopy && _backupNeedsFixing));
        }


    private:
        std::string _filename;
        bool _twoCopy;
        bool _primaryNeedsFixing;
        bool _backupNeedsFixing;
    };

    class sha1_ofstream : public std::ofstream, public sha1_fstream {
    public:
        sha1_ofstream(bool two_copy = false) : std::ofstream(), _twoCopy{ two_copy } {}
        explicit sha1_ofstream(const char* filename, std::ios_base::openmode mode = std::ios_base::out, bool two_copy = false) :
            std::ofstream(filename, mode),
            _twoCopy{ two_copy } {
            if (*this) _filename = filename;
        }
        explicit sha1_ofstream(const std::string& filename, std::ios_base::openmode mode = std::ios_base::out, bool two_copy = false) :
            std::ofstream(filename, mode),
            _twoCopy{ two_copy } {
            if (*this) _filename = filename;
        }

        // Get rid of all of the copy and move semantics
        sha1_ofstream(sha1_ofstream&& x) = delete;
        sha1_ofstream(const sha1_ofstream&) = delete;
        sha1_ofstream& operator=(sha1_ofstream&& _Right) = delete;
        void _Assign_rv(sha1_ofstream&& _Right) = delete;
        void swap(sha1_ofstream& _Right) = delete;

        ~sha1_ofstream() {
            close();
        }

        void open(const char* filename, std::ios_base::openmode mode = std::ios_base::out) {
            std::ofstream::open(filename, mode);
            if (*this) _filename = filename;
        }

        void open(const std::string& filename, ios_base::openmode mode = ios_base::out) {
            std::ofstream::open(filename, mode);
            if (*this) _filename = filename;
        }

        void close() {
            if (is_open()) {
                std::ofstream::close();

                std::string sha1;
                { // Open the file again to do the checksum.
                    std::ifstream ifs(_filename, std::ios_base::binary);
                    sha1 = detail::get_sha1(ifs);
                    ifs.close();
                }

                { // Save the checksum file.
                    std::string sha1_filename = _filename + ".sha1";
                    std::ofstream ofs(sha1_filename);
                    ofs << sha1;
                    ofs.close();
                }

                if (_twoCopy) {
                    // Make a backup file.
                    detail::copy_file(_filename, _filename + ".bak");

                    // Save the checksum file for the backup file.
                    std::string sha1_filename = _filename + ".bak.sha1";
                    std::ofstream ofs(sha1_filename);
                    ofs << sha1;
                    ofs.close();
                }

            }
        }

    private:
        std::string _filename;
        bool _twoCopy;
    };
}

#endif // SHA1_FSTREAM_HPP
