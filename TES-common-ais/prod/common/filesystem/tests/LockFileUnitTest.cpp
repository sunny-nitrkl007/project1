///////////////////////////////////////////////////////////////////////////////
/// @file      LockFileUnitTest.cpp
/// @date      June 24, 2025
/// @brief     A unit test for lock_file module.
///
/// @attention Copyright (C) Caterpillar Inc. All Rights Reserved.
///////////////////////////////////////////////////////////////////////////////

#define BOOST_TEST_MODULE LockFileTest
#include <boost/test/included/unit_test.hpp>
#include <filesystem/lock_file.hh>
#include <cstdio>
#include <unistd.h>

using namespace hub::filesystem;

BOOST_AUTO_TEST_SUITE(HubFilesystemLockFileTestSuite)

std::string lockfile("/tmp/lockfile_testXXXXXX.hlock");

BOOST_AUTO_TEST_CASE(LockUnlock) {
    lock_file lock(lockfile);
    BOOST_CHECK(lock.is_locked());
    lock.unlock();
    BOOST_CHECK(!lock.is_locked());
}

BOOST_AUTO_TEST_CASE(DoubleLockThrows) {
    lock_file lock1(lockfile);
    BOOST_CHECK_THROW(lock_file lock2(lockfile, 0.1, 1.0), hub::base::status_exception);
    lock1.unlock();
}

BOOST_AUTO_TEST_CASE(LockExpires) {
    lock_file lock1(lockfile);
    sleep(2); // Wait for lock to become stale
    //We should be able to create a new lock after the old one expires
    BOOST_CHECK_NO_THROW(lock_file lock2(lockfile, 0.5, 1.0)); //1.0 reap_timeout
}

BOOST_AUTO_TEST_CASE(RefreshLock) {
    lock_file lock(lockfile);
    BOOST_CHECK_NO_THROW(lock.refresh_lock());
    lock.unlock();
}

BOOST_AUTO_TEST_SUITE_END()