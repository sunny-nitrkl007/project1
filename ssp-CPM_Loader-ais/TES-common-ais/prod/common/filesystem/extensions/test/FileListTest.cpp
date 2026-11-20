///////////////////////////////////////////////////////////////////////////////
/// @file      FileListTest.cpp
/// @author    Steve Machan <Machan_Steve@cat.com>
/// @brief     Unit tests for the filelist
///
/// @attention Copyright (C) 2021
///////////////////////////////////////////////////////////////////////////////

// unit testing
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Unit tests for ros2_nvm::filesystem"

#include <ais/util/taskUtils.hpp>
#include <ais/util/test/boost_compat.h>
#include <filesystem/path.hh>
#include <filesystem/file.hh>
#include <filesystem/extensions/filelist.h>
#include <filesystem/extensions/file.h>
#include <unitTest/BoostUtils.hpp>

BOOST_AUTO_TEST_SUITE(filesystemTestSuite)

namespace fs = boost::filesystem;
namespace fl = ros2_nvm::filesystem::filelist;
namespace fhl = ros2_nvm::filesystem::file;

static constexpr auto RemovedFileLogLocation = "/tmp/fileListTestRemovedFiles";
static constexpr auto TestFileLocation = "/tmp/fileListUnitTest";

struct TestFixture
{
  TestFixture()
  {
    BOOST_TEST_MESSAGE("Use our _config dir for CAT_CONFIG_DIR");
    static const std::string configDir{getCATDirectory() + "/prod/coretech/hub/filesystem/extensions/test/_config/"};
    setenv("CAT_CONFIG_DIR", configDir.c_str(), 1);
  }
  ~TestFixture()
  {
    try
    {
      // cleanup
      fs::remove_all(getHomeDirectory() + TestFileLocation);
      fs::remove_all(TestFileLocation);
      fs::remove(RemovedFileLogLocation);
      BOOST_TEST_MESSAGE("Cleanup complete");
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      BOOST_CHECK(false);
    }
  }
};

BOOST_FIXTURE_TEST_CASE(fileSystemTest, TestFixture)
{
  std::string homeTestFileLocation = getHomeDirectory() + TestFileLocation;
  std::string tmpTestFileLocation{TestFileLocation};
  // Create files & dirs
  struct FileListTestStruct {
    std::string path;
    bool deleted; // Will the file/dir be deleted?
    bool logged;  // Will the file/dir deletion be logged (if an entire dir is deleted, its files will not be logged)?
  };
  std::vector<FileListTestStruct> dirs {
    {homeTestFileLocation + "/dir1", true, true},
    {homeTestFileLocation + "/dir2", false, false},
    {tmpTestFileLocation + "/dirNoSlash", true, true},
    {tmpTestFileLocation + "/dirSlash/", true, true},
    {tmpTestFileLocation + "/files", false, false},
    {tmpTestFileLocation + "/wildcards", false, false}
  };
  std::vector<FileListTestStruct> files {
    {homeTestFileLocation + "/file1", true, true},
    {homeTestFileLocation + "/file2", false, false},
    {tmpTestFileLocation + "/dirNoSlash/file1", true, false},
    {tmpTestFileLocation + "/dirNoSlash/file2", true, false},
    {tmpTestFileLocation + "/dirSlash/file3", true, false},
    {tmpTestFileLocation + "/dirSlash/file4", true, false},
    {tmpTestFileLocation + "/files/file1.txt", true, true},
    {tmpTestFileLocation + "/files/file2.txt", false, false},
    {tmpTestFileLocation + "/files/file3.txt", true, true},
    {tmpTestFileLocation + "/wildcards/file1.txt", true, true},
    {tmpTestFileLocation + "/wildcards/file2.txt", true, true},
    {tmpTestFileLocation + "/wildcards/file3.text", false, false},
    {tmpTestFileLocation + "/wildcards/prefix.out", true, true},
    {tmpTestFileLocation + "/wildcards/prefixes.yes", true, true},
    {tmpTestFileLocation + "/wildcards/inside.in", false, false},
    {tmpTestFileLocation + "/wildcards/inside.out", true, true},
  };

  // Create required dirs
  for (const auto& dir : dirs)
  {
    BOOST_REQUIRE(!fs::is_directory(dir.path));
    BOOST_TEST_MESSAGE("Creating " << dir.path);
    // Prune trailing '/' so that create_directories doesn't fail
    auto pathTrunc = (dir.path.back() == '/') ? dir.path.substr(0, dir.path.size() - 1) : dir.path;
    BOOST_CHECK(fs::create_directories(pathTrunc));
    BOOST_REQUIRE(fs::is_directory(pathTrunc));
  }

  // Create required dummy files
  auto dummyFile = getConfigFileDirectory() + "/dummy.txt";
  for (const auto& file : files)
  {
    BOOST_REQUIRE(!fs::exists(file.path));
    fs::copy_file(dummyFile, file.path);
    BOOST_REQUIRE(fs::exists(file.path));
  }

  // call filelist::get
  auto flashRemovalFileList = getConfigFileDirectory() + "/flashRemovalFileList.txt";
  auto fileList = fl::get(flashRemovalFileList);

  // call filelist::remove and check that the expected dirs/files were removed
  auto removedFiles = fl::remove(fileList);
  for (auto& dir : dirs)
  {
    BOOST_TEST_MESSAGE("Checking " << dir.path);
    BOOST_CHECK_EQUAL(std::find(removedFiles.begin(), removedFiles.end(), dir.path) != removedFiles.end(), dir.logged);
    BOOST_CHECK_EQUAL(fs::is_directory(dir.path), !dir.deleted);
  }
  for (auto& file : files)
  {
    BOOST_TEST_MESSAGE("Checking " << file.path);
    BOOST_CHECK_EQUAL(std::find(removedFiles.begin(), removedFiles.end(), file.path) != removedFiles.end(), file.logged);
    BOOST_CHECK_EQUAL(fs::exists(file.path), !file.deleted);
  }

  // Write removed files to disk and check that they match the expected
  hub::filesystem::file removedFileLogLocation{RemovedFileLogLocation};
  removedFileLogLocation.touch();
  ros2_nvm::filesystem::file::write(removedFileLogLocation.c_str(), removedFiles);
  BOOST_CHECK(ros2_nvm::filesystem::file::exists(removedFileLogLocation.str()));
  auto removedFilesLogged = fl::get(removedFileLogLocation.str());
  BOOST_REQUIRE(removedFilesLogged.size() == removedFiles.size());
  for (size_t i = 0; i < removedFiles.size(); i++)
  {
    BOOST_TEST_MESSAGE("removedFilesLogged[" << i << "]=" << removedFilesLogged[i] << " removedFiles[" << i << "]=" << removedFiles[i]);
    BOOST_CHECK_EQUAL(removedFilesLogged[i], removedFiles[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()
