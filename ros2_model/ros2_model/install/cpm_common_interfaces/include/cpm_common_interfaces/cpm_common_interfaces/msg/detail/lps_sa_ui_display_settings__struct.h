// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplaySettings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_settings.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'UNITS_METRIC'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__UNITS_METRIC = 0
};

/// Constant 'UNITS_ENGLISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__UNITS_ENGLISH = 1
};

/// Constant 'LANG_ENGLISH'.
/**
  * LpsSaUIDisplaySettingsLanguage
 */
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ENGLISH = 0
};

/// Constant 'LANG_SPANISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SPANISH = 1
};

/// Constant 'LANG_FRENCH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_FRENCH = 2
};

/// Constant 'LANG_PORTUGUESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_PORTUGUESE = 3
};

/// Constant 'LANG_GERMAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_GERMAN = 4
};

/// Constant 'LANG_NORWEGIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_NORWEGIAN = 5
};

/// Constant 'LANG_SWEDISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SWEDISH = 6
};

/// Constant 'LANG_FINNISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_FINNISH = 7
};

/// Constant 'LANG_DUTCH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_DUTCH = 8
};

/// Constant 'LANG_DANISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_DANISH = 9
};

/// Constant 'LANG_ITALIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ITALIAN = 10
};

/// Constant 'LANG_GREEK'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_GREEK = 11
};

/// Constant 'LANG_TURKISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_TURKISH = 12
};

/// Constant 'LANG_INDONESIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_INDONESIAN = 13
};

/// Constant 'LANG_RUSSIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_RUSSIAN = 14
};

/// Constant 'LANG_JAPANESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_JAPANESE = 15
};

/// Constant 'LANG_HUNGARIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_HUNGARIAN = 16
};

/// Constant 'LANG_ICELANDIC'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ICELANDIC = 17
};

/// Constant 'LANG_ARABIC'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ARABIC = 18
};

/// Constant 'LANG_TRADITIONAL_CHINESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_TRADITIONAL_CHINESE = 19
};

/// Constant 'LANG_CZECH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_CZECH = 20
};

/// Constant 'LANG_POLISH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_POLISH = 21
};

/// Constant 'LANG_SIMPLIFIED_CHINESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SIMPLIFIED_CHINESE = 22
};

/// Constant 'LANG_THAI'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_THAI = 23
};

/// Constant 'LANG_SLOVENIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SLOVENIAN = 24
};

/// Constant 'LANG_SLOVAKIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SLOVAKIAN = 25
};

/// Constant 'LANG_ESTONIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ESTONIAN = 26
};

/// Constant 'LANG_LATVIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_LATVIAN = 27
};

/// Constant 'LANG_LITHUANIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_LITHUANIAN = 28
};

/// Constant 'LANG_MALAYSIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_MALAYSIAN = 29
};

/// Constant 'LANG_KOREAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_KOREAN = 30
};

/// Constant 'LANG_PORTUGUESE_BRAZIL'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_PORTUGUESE_BRAZIL = 31
};

/// Constant 'LANG_FARSI'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_FARSI = 32
};

/// Constant 'LANG_HEBREW'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_HEBREW = 33
};

/// Constant 'LANG_SERBIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SERBIAN = 34
};

/// Constant 'LANG_CROATIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_CROATIAN = 35
};

/// Constant 'LANG_BULGARIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_BULGARIAN = 36
};

/// Constant 'LANG_ROMANIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ROMANIAN = 37
};

/// Constant 'LANG_VIETNAMESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_VIETNAMESE = 38
};

/// Constant 'LANG_MONGOLIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_MONGOLIAN = 39
};

/// Constant 'LANG_MACEDONIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_MACEDONIAN = 40
};

/// Constant 'LANG_BURMESE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_BURMESE = 41
};

/// Constant 'LANG_KHMER'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_KHMER = 42
};

/// Constant 'LANG_UKRAINIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_UKRAINIAN = 43
};

/// Constant 'LANG_SPANISH_CASTILIAN_EAME'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SPANISH_CASTILIAN_EAME = 44
};

/// Constant 'LANG_FRENCH_EAME'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_FRENCH_EAME = 45
};

/// Constant 'LANG_PORTUGUESE_EAME'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_PORTUGUESE_EAME = 46
};

/// Constant 'LANG_DUTCH_NETHERLANDS'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_DUTCH_NETHERLANDS = 47
};

/// Constant 'LANG_BURMESE_MYANMASA'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_BURMESE_MYANMASA = 48
};

/// Constant 'LANG_AFRIKAANS'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_AFRIKAANS = 49
};

/// Constant 'LANG_ALBANIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ALBANIAN = 50
};

/// Constant 'LANG_ARMENIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_ARMENIAN = 51
};

/// Constant 'LANG_BOSNIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_BOSNIAN = 52
};

/// Constant 'LANG_DARI'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_DARI = 53
};

/// Constant 'LANG_DUTCH_BELGIUM'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_DUTCH_BELGIUM = 54
};

/// Constant 'LANG_FRENCH_CANADIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_FRENCH_CANADIAN = 55
};

/// Constant 'LANG_HINDI'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_HINDI = 56
};

/// Constant 'LANG_KAZAKH'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_KAZAKH = 57
};

/// Constant 'LANG_LAOTIAN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_LAOTIAN = 58
};

/// Constant 'LANG_SPANISH_LACD'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_SPANISH_LACD = 59
};

/// Constant 'LANG_TAMIL'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_TAMIL = 60
};

/// Constant 'LANG_TURKMEN'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_TURKMEN = 61
};

/// Constant 'LANG_URDU'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__LANG_URDU = 62
};

/// Constant 'TIME_FORMAT_24HR'.
/**
  * Time Format
 */
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__TIME_FORMAT_24HR = 0
};

/// Constant 'TIME_FORMAT_12HR'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__TIME_FORMAT_12HR = 1
};

/// Constant 'DATE_FORMAT_YYYY_MM_DD'.
/**
  * Date Format
 */
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__DATE_FORMAT_YYYY_MM_DD = 1648
};

/// Constant 'DATE_FORMAT_MM_DD_YYYY'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__DATE_FORMAT_MM_DD_YYYY = 1649
};

/// Constant 'DATE_FORMAT_DD_MM_YYYY'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__DATE_FORMAT_DD_MM_YYYY = 1650
};

/// Constant 'KEYBOARD_QWERTY'.
/**
  * Keyboard Layout
 */
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__KEYBOARD_QWERTY = 0
};

/// Constant 'KEYBOARD_NATIVE'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__KEYBOARD_NATIVE = 1
};

/// Constant 'KEYBOARD_MIXED'.
enum
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings__KEYBOARD_MIXED = 2
};

/// Struct defined in msg/LpsSaUIDisplaySettings in the package cpm_common_interfaces.
/**
  * Units
 */
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplaySettings
{
  /// LpsSaUIDisplaySettings
  uint8_t units;
  uint16_t language;
  uint8_t brightness;
  uint8_t time_format;
  uint16_t date_format;
  int32_t weight_units;
  int32_t weight_precision;
  uint16_t service_mode_enable_code;
  uint8_t keyboard_layout_setting;
} cpm_common_interfaces__msg__LpsSaUIDisplaySettings;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaUIDisplaySettings.
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplaySettings__Sequence
{
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaUIDisplaySettings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_H_
