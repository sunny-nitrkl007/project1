///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2CgiDatum.h
/// @author    strubjc
/// @date      Mar 18, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2CGIDATUM_H_
#define JHM2CGIDATUM_H_

// These two must be included before other boost/serialization headers
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/map.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>

#include <ais/serialization/IsSerializable.h>


struct Jhm2CgiDatumAttributes
{
    Jhm2CgiDatumAttributes():
      pageNumber(0),
      totalPages(0)
    {}

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Serialize this type
  ///
  /// @param [in] ar - boost archive
  /// @param [in] version - version of class
  ///////////////////////////////////////////////////////////////////////////////
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & pageNumber & totalPages;
  }

  mutable unsigned int pageNumber;
  mutable unsigned int totalPages;
};

template<>
struct IsSerializable<Jhm2CgiDatumAttributes> {
  static const bool isSerializable = true;
};

BOOST_CLASS_VERSION(Jhm2CgiDatumAttributes, 0)
BOOST_CLASS_IMPLEMENTATION(Jhm2CgiDatumAttributes,boost::serialization::object_class_info)
BOOST_CLASS_TRACKING(Jhm2CgiDatumAttributes,boost::serialization::track_never)


template <typename T>
class Jhm2CgiDatum : public T, public boost::serialization::wrapper_traits<Jhm2CgiDatum<T> >
{
public:
  Jhm2CgiDatum() :T()
  {}
  explicit Jhm2CgiDatum(const T& baseCopy) : T(baseCopy)
  {}
  Jhm2CgiDatumAttributes attr;

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Serialize this datum
  ///
  /// @param [in] ar - boost archive
  /// @param [in] version - version of class
  ///////////////////////////////////////////////////////////////////////////////
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & attr; ///< First serialize attributes - always
    ar & boost::serialization::base_object<T>(*this); ///< serialize user object
  }

  Jhm2CgiDatumAttributes getAttr() const { return attr; }
  void setAttr( const unsigned int& pageNum, const unsigned int& pageTot )
  {
    attr.pageNumber = pageNum;
    attr.totalPages = pageTot;
  }
};

template<typename T>
struct IsSerializable<Jhm2CgiDatum<T> > {
  static const bool isSerializable = true;
};


#endif /* JHM2CGIDATUM_H_ */
