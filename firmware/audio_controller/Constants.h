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
enum{FIELD_COUNT_MAX=6};
enum{PARAMETER_COUNT_MAX=4};
enum{METHOD_COUNT_MAX=15};

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

extern const size_t bnc_a_pin;
extern const size_t bnc_b_pin;

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
    NOISE_TYPE,
  };

extern const char* const sd_prefix;

extern ConstantString device_name;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[]
extern ConstantString volume_field_name;
extern const double volume_min;
extern const double volume_max;
extern const double volume_default;

extern ConstantString trigger_frequency_left_field_name;
extern const long trigger_frequency_left_min;
extern const long trigger_frequency_left_max;
extern const long trigger_frequency_left_default;

extern ConstantString trigger_frequency_right_field_name;
extern const long trigger_frequency_right_min;
extern const long trigger_frequency_right_max;
extern const long trigger_frequency_right_default;

extern ConstantString trigger_a_duration_field_name;
extern const long trigger_a_duration_min;
extern const long trigger_a_duration_max;
extern const long trigger_a_duration_default;

extern ConstantString trigger_b_duration_field_name;
extern const long trigger_b_duration_min;
extern const long trigger_b_duration_max;
extern const long trigger_b_duration_default;

extern ConstantString trigger_a_right_field_name;
extern const bool trigger_a_right_default;

// Parameters
extern ConstantString audio_path_parameter_name;

extern ConstantString percent_parameter_name;
extern const int percent_min;
extern const int percent_max;

extern ConstantString frequency_parameter_name;
extern const int frequency_min;
extern const int frequency_max;

// Methods
extern ConstantString get_sd_card_info_method_name;
extern ConstantString get_audio_paths_method_name;
extern ConstantString play_path_method_name;
extern ConstantString play_tone_method_name;
extern ConstantString play_tone_left_method_name;
extern ConstantString play_tone_right_method_name;
extern ConstantString play_noise_method_name;
extern ConstantString play_noise_left_method_name;
extern ConstantString play_noise_right_method_name;
extern ConstantString stop_method_name;
extern ConstantString is_playing_method_name;
extern ConstantString get_last_audio_path_played_method_name;
extern ConstantString get_position_method_name;
extern ConstantString get_length_method_name;
extern ConstantString get_percent_complete_method_name;

// Errors
}
#endif
