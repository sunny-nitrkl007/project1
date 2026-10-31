#include <ais/serialization/Datum.h> // For Boost serialization
#include <string>

using namespace std;

#ifndef SCSCDATTIBRIDGEREADPARAMRESPONSE_H
#define SCSCDATTIBRIDGEREADPARAMRESPONSE_H

#define GPS_NORTHING_UID64 45459312551723013
#define GPS_EASTING_UID64 45459312551788549
#define GPS_ELEVATION_UID64 45459312551854085
#define GPS_ALTITUDE_UID64 45459312548839429
#define GPS_HEADING_UID64 45459312553820677
#define GPS_ACCURACY_UID64 45459312548511749

typedef enum 
{
  CDAParameterData_DATA_QUALITY_QUALITY_GOOD = 0,
  CDAParameterData_DATA_QUALITY_QUALITY_BAD = 1,
  CDAParameterData_DATA_QUALITY_QUALITY_NOT_RECEIVED = 2
} CDAParameterData_DATA_QUALITY_t;

class FileTransferBridgeReadParamResponseStorage : public csvable
{
public:
  typedef struct
  {
    double                          display_value{0.0};
    string                          display_string;   // parameter name
    CDAParameterData_DATA_QUALITY_t dsi{CDAParameterData_DATA_QUALITY_QUALITY_NOT_RECEIVED};
    string                          binary_value;
  } CDAParameterDataLocal_t;

  CDAParameterDataLocal_t      GPSNorthing;
  CDAParameterDataLocal_t      GPSEasting;
  CDAParameterDataLocal_t      GPSAltitude;
  CDAParameterDataLocal_t      GPSElevation;
  CDAParameterDataLocal_t      GPSHeading;
  CDAParameterDataLocal_t      GPSAccuracy;

  FileTransferBridgeReadParamResponseStorage() { }

  template <class Archive>
  void serialize(Archive &ar, unsigned int version)
  {
    ar & GPSNorthing.display_value;
    ar & GPSNorthing.display_string;
    ar & GPSNorthing.dsi;
    ar & GPSNorthing.binary_value;

    ar & GPSEasting.display_value;
    ar & GPSEasting.display_string;
    ar & GPSEasting.dsi;
    ar & GPSEasting.binary_value;

    ar & GPSAltitude.display_value;
    ar & GPSAltitude.display_string;
    ar & GPSAltitude.dsi;
    ar & GPSAltitude.binary_value;

    ar & GPSElevation.display_value;
    ar & GPSElevation.display_string;
    ar & GPSElevation.dsi;
    ar & GPSElevation.binary_value;

    ar & GPSHeading.display_value;
    ar & GPSHeading.display_string;
    ar & GPSHeading.dsi;
    ar & GPSHeading.binary_value;

    ar & GPSAccuracy.display_value;
    ar & GPSAccuracy.display_string;
    ar & GPSAccuracy.dsi;
    ar & GPSAccuracy.binary_value;
  }
  void toCsv(CsvOutStream& out) const
  {
    out("GPSNorthing.display_value", GPSNorthing.display_value);
    out("GPSNorthing.display_string", GPSNorthing.display_string);
    out("GPSNorthing.dsi", GPSNorthing.dsi);
    out("GPSNorthing.binary_value", GPSNorthing.binary_value);

    out("GPSEasting.display_value", GPSEasting.display_value);
    out("GPSEasting.display_string", GPSEasting.display_string);
    out("GPSEasting.dsi", GPSEasting.dsi);
    out("GPSEasting.binary_value", GPSEasting.binary_value);

    out("GPSAltitude.display_value", GPSAltitude.display_value);
    out("GPSAltitude.display_string", GPSAltitude.display_string);
    out("GPSAltitude.dsi", GPSAltitude.dsi);
    out("GPSAltitude.binary_value", GPSAltitude.binary_value);

    out("GPSElevation.display_value", GPSElevation.display_value);
    out("GPSElevation.display_string", GPSElevation.display_string);
    out("GPSElevation.dsi", GPSElevation.dsi);
    out("GPSElevation.binary_value", GPSElevation.binary_value);

    out("GPSHeading.display_value", GPSHeading.display_value);
    out("GPSHeading.display_string", GPSHeading.display_string);
    out("GPSHeading.dsi", GPSHeading.dsi);
    out("GPSHeading.binary_value", GPSHeading.binary_value);

    out("GPSAccuracy.display_value", GPSAccuracy.display_value);
    out("GPSAccuracy.display_string", GPSAccuracy.display_string);
    out("GPSAccuracy.dsi", GPSAccuracy.dsi);
    out("GPSAccuracy.binary_value", GPSAccuracy.binary_value);
  }

private:
   // Nothing here yet
};

typedef Datum<FileTransferBridgeReadParamResponseStorage> FileTransferBridgeReadParamResponse;

BOOST_CLASS_VERSION(FileTransferBridgeReadParamResponseStorage, 1);

#endif  //SCSCDATTIBRIDGEREADPARAMRESPONSE_H
