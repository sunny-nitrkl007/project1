///////////////////////////////////////////////////////////////////////////////
/// @file      DirTest.cpp
/// @author    Sandu Gherbe <sandu.gherbe@cat.com>
/// @brief     Unit tests for the dir
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
#include <filesystem/extensions/dir.h>
#include <filesystem/extensions/file.h>
#include <unitTest/BoostUtils.hpp>

BOOST_AUTO_TEST_SUITE(filesystemTestSuite)

namespace fs = boost::filesystem;
namespace fd = ros2_nvm::filesystem::nvm_dir;
namespace fl = ros2_nvm::filesystem::file;

static constexpr auto RemovedDirLogLocation = "/tmp/dirTestRemovedFiles";
static constexpr auto TestDirLocation = "/tmp/dirUnitTest";

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
      fs::remove_all(getHomeDirectory() + TestDirLocation);
      fs::remove_all(TestDirLocation);
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
  std::string homeTestDirLocation = getHomeDirectory() + TestDirLocation;
  std::string tmpTestDirLocation{TestDirLocation};
  // Create files & dirs
  std::vector<std::string> dirs {
    { "/emptyDir/"}, //0
    {"/rootDir/subDir1/"},//1
    { "/rootDir/subDir1/subSubDirFolder1"}, //2
    { "/rootDir/subDir1/subSubDirFolder2"}, //3
    {"/rootDir/subRootFolder1"},  //4
    { "/rootDirFolder2"}, //5
  };

  std::vector<std::string> files {
    {"/file1.ext"}, //0
    {"/file1.txt"}, //1
    {"/file3.a"}, //2
    {"/fileFileFileFi.cpp"}, //3
    {"/cppHeader.h"}, //4
    {"/txtFile.txt"}  //5
  };

  const std::string fileContent{"uierhfnr;oi c nhiefjv;iwoerfj e;oirfjoi;wehx;iofejfrthgcf;iwefjpo;qwfioexuhrfliw\noueirhtqpehpoqiwnufqpfcoiqweuqouiweyfioqcuoie"};


  //Create required dirs
  for (const auto& dir : dirs)
  {
    hub::filesystem::path pathHome{homeTestDirLocation + dir};
    hub::filesystem::path pathTmp{tmpTestDirLocation + dir};
    BOOST_REQUIRE(!pathHome.exists());
    BOOST_REQUIRE(!pathTmp.exists());
    BOOST_TEST_MESSAGE("Creating " << dir);
    BOOST_CHECK(fd::create(pathHome.str()));
    BOOST_CHECK(fd::create(pathTmp.str()));
    BOOST_REQUIRE(pathHome.is_directory());
    BOOST_REQUIRE(pathTmp.is_directory());
  }

  //create some files inside folders
  //{
    hub::filesystem::file file1SubDir1(tmpTestDirLocation + dirs[1], files[0]);
    file1SubDir1.touch();
    hub::filesystem::file file2SubDir1(tmpTestDirLocation + dirs[1], files[1]);
    file2SubDir1.touch();
    hub::filesystem::file file3SubDir1(tmpTestDirLocation + dirs[1], files[4]);
    file3SubDir1.touch();
    file3SubDir1.write_entirely(fileContent);
    hub::filesystem::file file4SubDir1(tmpTestDirLocation + dirs[1], files[5]);
    file4SubDir1.touch();
    hub::filesystem::file file1subSubDirFolder1(homeTestDirLocation +dirs[2], files[3]);
    file1subSubDirFolder1.touch();
    hub::filesystem::file file1subSubDirFolder1Tmp(tmpTestDirLocation +dirs[3], files[3]);
    file1subSubDirFolder1Tmp.touch();
    hub::filesystem::file file2subSubDirFolder1(homeTestDirLocation + dirs[2], files[2]);
    file2subSubDirFolder1.touch();
    hub::filesystem::file fileRootDirFolder(tmpTestDirLocation + dirs[5], files[4]);
    fileRootDirFolder.touch();
  //}

  //copy folders
  {
    hub::filesystem::path destHomeDirPath(homeTestDirLocation + "/dir-copy");
    hub::filesystem::path destTmoDirPath(tmpTestDirLocation + "/dir_copy");
    BOOST_CHECK(fd::create(destHomeDirPath.str()));
    BOOST_CHECK(fd::create(destTmoDirPath.str()));
    BOOST_CHECK(fd::copy(homeTestDirLocation + dirs[2], destHomeDirPath.str()));
    BOOST_CHECK(fd::copy(tmpTestDirLocation + dirs[3], destTmoDirPath.str()));
    BOOST_CHECK(fd::copy(tmpTestDirLocation + dirs[0], destHomeDirPath.str()));
    BOOST_CHECK(fd::copy(tmpTestDirLocation + dirs[1], destTmoDirPath.str()));
    //BOOST_REQUIRE()
  }

  {
    hub::filesystem::file tmpItem(homeTestDirLocation + "/dir-copy/" + files[2]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  {
    hub::filesystem::file tmpItem(homeTestDirLocation + "/dir-copy/" + files[3]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  {
    hub::filesystem::file tmpItem(tmpTestDirLocation + "/dir_copy/" + files[4]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() > 0);
  }

  {
    hub::filesystem::file tmpItem(tmpTestDirLocation + "/dir_copy/" + files[0]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  {
    hub::filesystem::file tmpItem(tmpTestDirLocation + "/dir_copy/" + files[1]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  {
    hub::filesystem::file tmpItem(tmpTestDirLocation + "/dir_copy/" + files[5]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  {
    hub::filesystem::path tmpItem(tmpTestDirLocation + "/dir_copy/" + "subSubDirFolder1");
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_directory());
  }

  {
    hub::filesystem::path tmpItem(tmpTestDirLocation + "/dir_copy/" + "subSubDirFolder2");
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_directory());
  }

  {
    hub::filesystem::file tmpItem(tmpTestDirLocation + "/dir_copy/" + "/subSubDirFolder2/" + files[3]);
    BOOST_REQUIRE(tmpItem.exists() && tmpItem.is_regular_file() && tmpItem.get_size() == 0);
  }

  //select some files based on extensions
  {
    fd::PathList pl;
    BOOST_CHECK(fd::getFilePaths(tmpTestDirLocation+ dirs[1], pl, "txt"));
    BOOST_REQUIRE(pl.size() == 2);
    pl.clear();
    BOOST_CHECK(fd::getFilePaths(tmpTestDirLocation + dirs[1], pl, "ext"));
    BOOST_REQUIRE(pl.size() == 1);
    pl.clear();
    BOOST_CHECK(fd::getFilePaths(tmpTestDirLocation + dirs[1], pl, ""));
    BOOST_REQUIRE(pl.size() == 4);
    pl.clear();
    BOOST_CHECK(fd::getFilePaths(tmpTestDirLocation + dirs[1], pl));
    BOOST_REQUIRE(pl.size() == 4);
    pl.clear();
    BOOST_CHECK(fd::getFilePaths(tmpTestDirLocation + dirs[1], pl, "abc"));
    BOOST_REQUIRE(pl.size() == 0);
  }

  //Delete previously created folders
  {
    BOOST_CHECK(fd::clear(tmpTestDirLocation + dirs[1]));
    hub::filesystem::path dir1Path(tmpTestDirLocation + dirs[2]);
    hub::filesystem::path dir2Path(tmpTestDirLocation + dirs[3]);
    BOOST_REQUIRE(!dir1Path.exists());
    BOOST_REQUIRE(!dir2Path.exists());
  }
}

BOOST_AUTO_TEST_SUITE_END()
