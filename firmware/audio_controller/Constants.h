// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"

namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{FIELD_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=2};
enum{METHOD_COUNT_MAX=10};

enum{AUDIO_EXT_COUNT=2};
enum{STRING_LENGTH_PATH=255};
enum{STRING_LENGTH_ERROR_MESSAGE=257};

extern const size_t led_pin;

extern const size_t baudrate;

extern const size_t model_number;

extern HardwareSerial serial2;

extern const long firmware_major;
extern const long firmware_minor;
extern const long firmware_patch;

extern const size_t sd_card_cs_pin;
extern const size_t sd_card_mosi_pin;
extern const size_t sd_card_sck_pin;

extern const char* const audio_ext_raw;
extern const char* const audio_ext_wav;
extern const char* const audio_exts[AUDIO_EXT_COUNT];
enum audio_t
  {
    RAW_TYPE,
    WAV_TYPE,
    TONE_TYPE,
  };

extern const char* const sd_prefix;

extern ConstantString device_name;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[]
extern ConstantString volume_field_name;
extern const double volume_min;
extern const double volume_max;
extern const double volume_default;

// Parameters
extern ConstantString audio_path_parameter_name;

extern ConstantString percent_parameter_name;
extern const int percent_min;
extern const int percent_max;

// Methods
extern ConstantString get_sd_card_info_method_name;
extern ConstantString get_audio_paths_method_name;
extern ConstantString play_path_method_name;
extern ConstantString play_tone_method_name;
extern ConstantString stop_method_name;
extern ConstantString is_playing_method_name;
extern ConstantString get_last_audio_path_played_method_name;
extern ConstantString get_position_method_name;
extern ConstantString get_length_method_name;
extern ConstantString get_percent_complete_method_name;

// Errors
}
#endif
