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
enum{SAVED_VARIABLE_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=2};
enum{METHOD_COUNT_MAX=10};

enum{AUDIO_EXT_COUNT=2};
enum{STRING_LENGTH_PATH=255};
enum{STRING_LENGTH_ERROR_MESSAGE=257};

extern const int led_pin;

extern const unsigned int baudrate;

extern const unsigned int model_number;

extern HardwareSerial serial2;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern const unsigned int sd_card_cs_pin;
extern const unsigned int sd_card_mosi_pin;
extern const unsigned int sd_card_sck_pin;

extern const char* const audio_ext_raw;
extern const char* const audio_ext_wav;
extern const char* const audio_exts[AUDIO_EXT_COUNT];
enum audio_file_t
  {
    RAW_TYPE,
    WAV_TYPE
  };

extern const char* const sd_prefix;

extern const int percent_min;
extern const int percent_max;

extern ConstantString device_name;

extern ConstantString audio_path_parameter_name;
extern ConstantString percent_parameter_name;

extern ConstantString get_sd_card_info_method_name;
extern ConstantString get_audio_paths_method_name;
extern ConstantString play_method_name;
extern ConstantString is_playing_method_name;
extern ConstantString stop_method_name;
extern ConstantString get_last_audio_path_played_method_name;
extern ConstantString set_volume_method_name;
extern ConstantString get_position_method_name;
extern ConstantString get_length_method_name;
extern ConstantString get_percent_complete_method_name;
}
#endif
