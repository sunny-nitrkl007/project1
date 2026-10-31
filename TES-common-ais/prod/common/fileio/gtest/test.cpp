#include <fstream>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

#include <sha1_fstream.hpp>

namespace {

namespace fs = boost::filesystem;
using namespace tes_common_ais;

bool compare_files(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; // size mismatch
    }

    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
            std::istreambuf_iterator<char>(),
            std::istreambuf_iterator<char>(f2.rdbuf()));
}

// The fixture for testing class Foo.
class SHA1FStreamTest : public ::testing::Test {

protected:
   // You can remove any or all of the following functions if its body
   // is empty.

    SHA1FStreamTest() {
        fs::path tempRoot = fs::temp_directory_path();
        fs::path tempSubDir = fs::path{"%%%%-%%%%-%%%%-%%%%"};
        tempDir = fs::unique_path(tempRoot / tempSubDir);
    }

    virtual ~SHA1FStreamTest() {
    }

    virtual void SetUp() {
        // Maybe we want this to be an ::testing::Environment SetUp?
        fs::create_directory(tempDir);
        ASSERT_TRUE(fs::exists(tempDir));
    }

    virtual void TearDown() {
        // Maybe we want this to be an ::testing::Environment TearDown?
        fs::remove_all(tempDir);
    }

    // Objects declared here can be used by all tests in the test case.
    fs::path tempDir;
};

TEST_F(SHA1FStreamTest, FilesIdentical) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filename);
    EXPECT_TRUE(ofs);

    ofs << test_string;
    ofs.close();

    EXPECT_TRUE(fs::exists(filename));
    EXPECT_TRUE(fs::exists(filename_sha1));
    EXPECT_TRUE(fs::exists(filename_bak));
    EXPECT_TRUE(fs::exists(filename_bak_sha1));

    EXPECT_TRUE(compare_files(filename, filename_bak));
    EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));

    sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filename);
    EXPECT_TRUE(ifs);

    std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    EXPECT_EQ(test_string, result_string);

    ifs.close();

    sha1_fstream::remove_files(filename);
    EXPECT_FALSE(fs::exists(filename));
    EXPECT_FALSE(fs::exists(filename + ".sha1"));
    EXPECT_FALSE(fs::exists(filename + ".bak"));
    EXPECT_FALSE(fs::exists(filename + ".bak.sha1"));
}

TEST_F(SHA1FStreamTest, File1CorruptOrMissing) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create the file
        sha1_ofstream ofs{ true }; // two_copy
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Corrupt the file
        std::ofstream ofs(filename);
        ofs << "";
        ofs.close();
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_TRUE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_TRUE(ifs.fix_it());
        EXPECT_FALSE(ifs.is_corrupt());
        std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        EXPECT_EQ(test_string, result_string);
        ifs.close();
    }

    { // Is it fixed?
        EXPECT_TRUE(compare_files(filename, filename_bak));
        EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));
    }
}

TEST_F(SHA1FStreamTest, File1SHA1CorruptOrMissing) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create the file
        sha1_ofstream ofs{ true }; // two_copy
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Corrupt the file
        std::ofstream ofs(filename_sha1);
        ofs << "";
        ofs.close();
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_TRUE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_TRUE(ifs.fix_it());
        EXPECT_FALSE(ifs.is_corrupt());
        std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        EXPECT_EQ(test_string, result_string);
        ifs.close();
    }

    { // Is it fixed?
        EXPECT_TRUE(compare_files(filename, filename_bak));
        EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));
    }
}

TEST_F(SHA1FStreamTest, File2CorruptOrMissing) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create the file
        sha1_ofstream ofs{ true }; // two_copy
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Corrupt the file
        std::ofstream ofs(filename_bak);
        ofs << "";
        ofs.close();
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_TRUE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_TRUE(ifs.fix_it());
        EXPECT_FALSE(ifs.is_corrupt());
        std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        EXPECT_EQ(test_string, result_string);
        ifs.close();
    }

    { // Is it fixed?
        EXPECT_TRUE(compare_files(filename, filename_bak));
        EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));
    }
}

TEST_F(SHA1FStreamTest, File2SHA1CorruptOrMissing) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create the file
        sha1_ofstream ofs{ true }; // two_copy
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Corrupt the file
        fs::remove(filename_bak_sha1);
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_TRUE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_TRUE(ifs.fix_it());
        EXPECT_FALSE(ifs.is_corrupt());
        std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        EXPECT_EQ(test_string, result_string);
        ifs.close();
    }

    { // Is it fixed?
        EXPECT_TRUE(compare_files(filename, filename_bak));
        EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));
    }
}

TEST_F(SHA1FStreamTest, BothCorrupt) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create the file
        sha1_ofstream ofs{ true }; // two_copy
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Corrupt the file
        fs::remove(filename_sha1);
        fs::remove(filename_bak_sha1);
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_FALSE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_FALSE(ifs.fix_it());
        EXPECT_TRUE(ifs.is_corrupt());
        ifs.close();
    }
}

TEST_F(SHA1FStreamTest, File2Different) {
    const std::string test_string = "This is a test.";
    const std::string filename = (tempDir / "test.txt").string();
    const std::string filename_sha1 = filename + ".sha1";
    const std::string filename_bak = filename + ".bak";
    const std::string filename_bak_sha1 = filename + ".bak.sha1";

    { // Create file 1
        sha1_ofstream ofs;
        ofs.open(filename);
        EXPECT_TRUE(ofs);
        ofs << test_string;
        ofs.close();
    }

    { // Create file 2
        sha1_ofstream ofs;
        ofs.open(filename_bak);
        EXPECT_TRUE(ofs);
        ofs << "";
        ofs.close();
    }

    { // Check results
        sha1_ifstream ifs{ true }; // two_copy
        ifs.open(filename);
        EXPECT_TRUE(ifs);
        EXPECT_TRUE(ifs.is_corrupt());
        EXPECT_TRUE(ifs.fix_it());
        EXPECT_FALSE(ifs.is_corrupt());
        std::string result_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        EXPECT_EQ(test_string, result_string);
        ifs.close();
    }

    { // Is it fixed?
        EXPECT_TRUE(compare_files(filename, filename_bak));
        EXPECT_TRUE(compare_files(filename_sha1, filename_bak_sha1));
    }
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
