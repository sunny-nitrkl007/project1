///////////////////////////////////////////////////////////////////////////////
/// @file      Dirtest2.cpp
/// @author    Steve Machan <Machan_Steve@cat.com>
/// @brief     Unit tests for dir
///
/// @attention Copyright (C) 2021
///////////////////////////////////////////////////////////////////////////////

// unit testing
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Unit tests for ros2_nvm::filesystem"

#include <boost/algorithm/string/predicate.hpp>

#include "rclcpp/rclcpp.hpp"
#include <ais/util/taskUtils.hpp>
#include <ais/util/test/boost_compat.h>
#include <filesystem/path.hh>
#include <filesystem/file.hh>
#include <filesystem/extensions/dir.h>
#include <unitTest/BoostUtils.hpp>

BOOST_AUTO_TEST_SUITE(filesystemTestSuite)

namespace fs = boost::filesystem;
namespace nvm_fs = ros2_nvm::filesystem;

static constexpr auto TestFileLocation = "/tmp/aisFilesystemDirTest/";

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
      fs::remove_all(TestFileLocation);
      BOOST_TEST_MESSAGE("Cleanup complete");
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      BOOST_CHECK(false);
    }
  }
};

BOOST_FIXTURE_TEST_CASE(getFilePaths, TestFixture)
{
  logger::SingletonLogger().Instance()->setWriterThresholds(logger::Priority::debug);
  std::string tmpTestFileLocation{TestFileLocation};
  // Create files
  std::vector<std::string> files {
    {tmpTestFileLocation + "file2"},
    {tmpTestFileLocation + "file1"},
    {tmpTestFileLocation + "file1.txt"},
    {tmpTestFileLocation + "file2.txt"},
    {tmpTestFileLocation + "prefix.out"},
    {tmpTestFileLocation + "prefixes.yes"},
    {tmpTestFileLocation + "inside.in"},
    {tmpTestFileLocation + "inside.out"},
  };

  // Create required dir
  {
    auto dir = tmpTestFileLocation;
    BOOST_REQUIRE(!fs::is_directory(dir));
    BOOST_TEST_MESSAGE("Creating " << dir);
    // Prune trailing '/' so that create_directories doesn't fail
    auto pathTrunc = (dir.back() == '/') ? dir.substr(0, dir.size() - 1) : dir;
    BOOST_CHECK(fs::create_directories(pathTrunc));
    BOOST_REQUIRE(fs::is_directory(pathTrunc));
  }

  // Create required dummy files
  auto dummyFile = getConfigFileDirectory() + "/dummy.txt";
  for (const auto& file : files)
  {
    BOOST_TEST_MESSAGE("Creating dummy file: " << file);
    BOOST_REQUIRE(!fs::exists(file));
    fs::copy_file(dummyFile, file);
    BOOST_REQUIRE(fs::exists(file));
  }

  // call getFilePaths with a wildcard
  {
    nvm_fs::nvm_dir::PathList pathList;
    BOOST_REQUIRE(nvm_fs::nvm_dir::getFilePaths(tmpTestFileLocation, pathList, ".txt"));

    // Check that the number of files matches the expected
    auto numTxtFiles = std::count_if(files.begin(), files.end(),
      [] (std::string file) { return boost::algorithm::ends_with(file, ".txt"); });
    BOOST_CHECK_GT(pathList.size(), 0);
    BOOST_CHECK_EQUAL(pathList.size(), numTxtFiles);

    // Check that only .txt files were found and are alphabetical
    hub::filesystem::path filePrev;
    for (auto& file : pathList)
    {
      BOOST_CHECK(boost::algorithm::ends_with(file.str(), ".txt"));
      BOOST_CHECK(file > filePrev);
      auto it = std::find(files.begin(), files.end(), file.str());
      BOOST_CHECK(it != files.end());
      filePrev = file;
    }
  }

  // call getFilePaths without a wildcard
  {
    nvm_fs::nvm_dir::PathList pathList;
    BOOST_REQUIRE(nvm_fs::nvm_dir::getFilePaths(tmpTestFileLocation, pathList));
    BOOST_CHECK_GT(pathList.size(), 0);

    // Check that all files were found and are alphabetical
    BOOST_CHECK_EQUAL(pathList.size(), files.size());
    hub::filesystem::path filePrev;
    for (auto& file : pathList)
    {
      BOOST_CHECK(file > filePrev);
      auto it = std::find(files.begin(), files.end(), file.str());
      BOOST_CHECK(it != files.end());
      filePrev = file;
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
