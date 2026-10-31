///////////////////////////////////////////////////////////////////////////////
/// @file      FileTest.cpp
/// @author    Sandu Gherbe <sandu.gherbe@cat.com>
/// @brief     Unit tests for the file
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
#include <filesystem/extensions/file.h>
#include <unitTest/BoostUtils.hpp>
#include <algorithm>

BOOST_AUTO_TEST_SUITE(filesystemTestSuite)

namespace fs = boost::filesystem;
namespace fl = ros2_nvm::filesystem::file;
namespace fd = ros2_nvm::filesystem::nvm_dir;

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

  const std::string flashFileTail = "/flashRemovalFileList.txt";

  const std::string invalidFile{homeTestFileLocation + "invalidFile.xyz"};
  const std::string destFileSameName{homeTestFileLocation + "/file1/"};
  const std::string destFileNoExtension{homeTestFileLocation + "/file2"};
  const std::string destFileDiffName{homeTestFileLocation + "/files/file.txt"};

  //check file exists
  {
    auto dummyFile = getConfigFileDirectory() + "/dummy.txt";
    auto flashRemovalFileList = getConfigFileDirectory() + flashFileTail;
    auto inexistentFile = getConfigFileDirectory() + "inexistentFile.abc";
    hub::filesystem::file dmmyFile{dummyFile};
    hub::filesystem::file flashRmvalFileList(flashRemovalFileList);
    hub::filesystem::file inxstntFile(inexistentFile);
    BOOST_REQUIRE(fl::exists(dmmyFile.str()));
    BOOST_REQUIRE(fl::exists(flashRmvalFileList.str()));
    BOOST_REQUIRE(!fl::exists(inxstntFile.str()));

    //test file copy
    //copy existing file with different destination name
    hub::filesystem::path destFileDifferentName(destFileDiffName);
    BOOST_CHECK(fl::copy(flashRmvalFileList.str(), destFileDifferentName.str()));
    BOOST_REQUIRE(fl::exists(destFileDifferentName.str()));
    BOOST_REQUIRE(fl::areIdentical(destFileDifferentName.str(), flashRmvalFileList.str()));

    //copy existing file with destination name with no extension
    hub::filesystem::path destFileNoExt(destFileNoExtension);
    BOOST_CHECK(fl::copy(flashRmvalFileList.str(), destFileNoExt.str()));
    BOOST_REQUIRE(fl::exists(destFileNoExt.str()));
    BOOST_REQUIRE(fl::areIdentical(destFileNoExt.str(), flashRmvalFileList.str()));

    //copy file to destination with same file name in directory ends /
    hub::filesystem::path destFileSameNme{destFileSameName};
    // append "/" to the end of the destination so copy recognizes it as a directory
    BOOST_CHECK(fl::copy(flashRmvalFileList.str(), destFileSameNme.str() + "/"));
    hub::filesystem::file resultFile (destFileSameNme, flashFileTail);
    BOOST_REQUIRE(fl::exists(resultFile.str()));
    BOOST_REQUIRE(fl::areIdentical(flashRmvalFileList.str(), resultFile.str()));

    //copy file and overwrite
    BOOST_CHECK(fl::copy(flashRmvalFileList.str(), destFileSameNme.str() + "/", true));
    BOOST_REQUIRE(fl::exists(resultFile.str()));
    BOOST_REQUIRE(fl::areIdentical(flashRmvalFileList.str(), resultFile.str()));

    //copy inexistent file
    hub::filesystem::path invalidFilePath{invalidFile};
    BOOST_CHECK(!fl::copy(invalidFilePath.str(), destFileDifferentName.str()));
    BOOST_REQUIRE(!fl::areIdentical(invalidFilePath.str(), destFileDifferentName.str()));

    //check read and copy
    std::string fileContent;
    BOOST_CHECK(fl::read(dmmyFile.str(), fileContent));
    BOOST_REQUIRE(fileContent.size() > 0);
    std::stringstream fileContentStream;
    BOOST_CHECK(fl::read(dmmyFile.str(), fileContentStream));
    BOOST_REQUIRE(fileContentStream.str().size() > 0);

    hub::filesystem::file destWFile(tmpTestFileLocation + "/file.txt");
    hub::filesystem::path dir(tmpTestFileLocation);
    fd::create(dir.str());
    destWFile.touch();
    BOOST_CHECK(fl::write(destWFile.str(), fileContent));
    BOOST_REQUIRE(fl::areIdentical(dmmyFile.str(), destWFile.str()));

    std::vector<std::string> strVct;
    std::copy(std::istream_iterator<std::string>(fileContentStream), std::istream_iterator<std::string>(), std::back_inserter(strVct));
    hub::filesystem::file destWFile2(tmpTestFileLocation + "/file2.txt");
    destWFile2.touch();
    BOOST_CHECK(fl::write(destWFile2.str(), fileContent));
    BOOST_REQUIRE(fl::areIdentical(dmmyFile.str(), destWFile2.str()));

    // check areIdentical with equal file sizes
    BOOST_CHECK(fl::write(destWFile.str(), fileContent));
    fileContent[0] = '!';
    BOOST_CHECK(fl::write(destWFile2.str(), fileContent));
    BOOST_CHECK(!fl::areIdentical(destWFile.str(), destWFile2.str()));

    //check file removal
    BOOST_CHECK(fl::remove(destWFile.str()));
    BOOST_REQUIRE(!fl::exists(destWFile.str()));

    BOOST_CHECK(fl::remove(destFileDifferentName.str()));
    BOOST_REQUIRE(!fl::exists(destFileDifferentName.str()));
  }

}

BOOST_AUTO_TEST_SUITE_END()
