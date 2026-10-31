///////////////////////////////////////////////////////////////////////////////
/// @file      nvmStorageExample.hpp
/// @author    Steve Machan <Machan_Steve@cat.com>
///
/// @brief     Example use of NvmStorage
///
/// @attention Copyright (C) 2021
/// @attention Caterpillar
/// @attention All rights reserved
///////////////////////////////////////////////////////////////////////////////

#ifndef NVMSTORAGEEXAMPLE_H
#define NVMSTORAGEEXAMPLE_H

#include <filesystem/extensions/nvmStorage.hpp>

struct NvmStorageStruct
{
public:
   // Optional accessor functions for data members that set NvmStorage::saveNeeded
   uint16_t getExample1() const { return m_example1; }
   void setExample1(uint16_t example1) { m_example1 = example1; saveNeeded(true); }

   double getExample2() const { return m_example2; }
   void setExample2(double example1) { m_example2 = example2; saveNeeded(true); }

   std::vector<std::string> getExample3() const { return m_example3; }
   void setExample3(std::vector<std::string>&& example3) { m_example3 = std::move(example3); saveNeeded(true); }

private:
   // Serializable data members. Can either be public (POD) or provided through accessor functions.
   uint16_t m_example1;
   double m_example2;
   std::vector<std::string> m_example3;

   // Required for serialize to be private/protected
   friend class boost::serialization::access;

   // Required for boost::serialization.
   template<class Archive>
   void serialize(Archive& ar, const unsigned int version)
   {
      ar & m_example1;
      ar & m_example2;
      ar & m_example3;
   }

   // For asymmetrical serialization/deserialization, separate save/load can be implemented in place of serialize
   // template<class Archive>
   // void load(Archive &ar, unsigned int version)
   // {
   //    ar >> m_example1;
   //    double example2Dummy;
   //    ar >> example2Dummy;  // No longer used, but included for backwards compatibility
   //    ar >> m_example3;
   // }

   // template<class Archive>
   // void save(Archive &ar, unsigned int version)
   // {
   //    ar << m_example1;
   //    ar << m_example2;
   //    ar << m_example3;
   // }
};

BOOST_CLASS_VERSION(NvmStorageStruct, 0);

// The object used by the task will be of type NvmStorageExample
using NvmStorageExample = ros2_nvm::filesystem::NvmStorage<NvmStorageStruct>;

#endif
