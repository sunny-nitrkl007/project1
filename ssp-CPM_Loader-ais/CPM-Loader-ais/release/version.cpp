#include <stdio.h>
#include <cstring>
#include <stdint.h>
#include <hub/lib_module/ecminfolib_public.h>
#include <hub/lib_module/applib_public.h>
#include "commit_sha.h"
#include "version.h"
#include "legal_for_trade_identifiers.h"

#define Q(x) #x
#define QUOTE(x) Q(x)

constexpr size_t SoftwarePartNumberLength = 7;
constexpr size_t SoftwareChangeNumberLength = 2;

// Concatenation of softwarePartNumber and softwareChangeNumber
char softwareGroupPartNumber[SOFTWARE_GROUP_PN_LENGTH + 1];

const char swversion[]= QUOTE(SWVERSION) " " COMMIT_SHA;
const char buildTree[]= "$Head: " COMMIT_SHA "$";

const char softwarePartNumber[]         =  QUOTE(SOFTWARE_PART_NUMBER);
const char softwareChangeNumber[]       =  QUOTE(SOFTWARE_CHANGE_NUMBER);
const char softwareGroupReleaseDate[]   =  QUOTE(SOFTWARE_RELEASE_DATE);
const char softwareGroupDescription[]   =  QUOTE(SOFTWARE_GROUP_DESCRIPTION);
const char softwareNameCode[]           =  QUOTE(SOFTWARE_NAME_CODE);
const int_least16_t FlashApplicationIdentifier = FLASH_APPLICATION_ID;
const int_least16_t FlashComponentIdentifier   = FLASH_COMPONENT_ID;

/*
 * Payload Legal For Trade (LFT) Measurement Software Identifier
 * ----------------------------------------------------------------------------
 * Used to read the identifier inextricably linked to the legally relevant
 * payload measurement software. The Payload Legal For Trade Measurement
 * Software Identifier only represents the legally relevant portion of
 * software. For example, this software identification could be altered for
 * every software change that may affect the metrological functions of the
 * instrument. This identifier is application specific.
 *
 * Standalone product variant is 4.0
 * Build string format is DDMMMYYYY such as 10May2023
 */
#ifndef LFT_SW_ID_VERSION
//#error "LFT_SW_ID_VERSION is not defined."
#define LFT_SW_ID_VERSION=4.1
#endif
const std::string legal_for_trade_software_id_version(QUOTE(LFT_SW_ID_VERSION));
const std::string legal_for_trade_software_id_build{__DATE__[4], __DATE__[5], __DATE__[0], __DATE__[1], __DATE__[2], __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10]};


void version()
{
    printf( "Software Version:            %s\n", swversion );
    // printf( "Build Tree:                  %s\n", buildTree );
    printf( "Software Group Part Number:  %s-%s\n", softwarePartNumber, softwareChangeNumber);
    printf( "Software Group Release Date: %s\n", softwareGroupReleaseDate);
    printf( "Software Group Description:  %s\n", softwareGroupDescription);
}


///////////////////////////////////////////////////////////////////////////////
/// @brief  
///////////////////////////////////////////////////////////////////////////////
const char * getversion()
{
  return swversion;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
const char * getBuildTree()
{
  return buildTree;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
const char * getSoftwarePartNumber()
{
  return softwarePartNumber;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
const char * getSoftwareChangeNumber()
{
  return softwareChangeNumber;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
const char * getSoftwareNameCode()
{
  return softwareNameCode;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
uint_least16_t getFlashApplicationIdentifier()
{
  return FlashApplicationIdentifier;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief 
///////////////////////////////////////////////////////////////////////////////
uint_least16_t getFlashComponentIdentifier()
{
  return FlashComponentIdentifier;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief  
///////////////////////////////////////////////////////////////////////////////
//cppcheck-suppress unusedFunction
const char * getSoftwareGroupPartNumber()
{
  softwareGroupPartNumber[0] = 0;
  strncpy(softwareGroupPartNumber, softwarePartNumber, SoftwarePartNumberLength);
  strncat(softwareGroupPartNumber, "-", 1);
  strncat(softwareGroupPartNumber, softwareChangeNumber, SoftwareChangeNumberLength);
  softwareGroupPartNumber[SOFTWARE_GROUP_PN_LENGTH] = 0;
  return softwareGroupPartNumber;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief  
///////////////////////////////////////////////////////////////////////////////
//cppcheck-suppress unusedFunction
const char * getSoftwareGroupDescription()
{
  return softwareGroupDescription;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief  
///////////////////////////////////////////////////////////////////////////////
//cppcheck-suppress unusedFunction
const char * getSoftwareGroupReleaseDate()
{
  return softwareGroupReleaseDate;
}
