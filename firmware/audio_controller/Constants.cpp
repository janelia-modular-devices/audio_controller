// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const size_t led_pin = 13;

const size_t baudrate = 9600;

const size_t model_number = 1150;

HardwareSerial serial2(Serial2);

// Use semantic versioning http://semver.org/
const long firmware_major = 0;
const long firmware_minor = 1;
const long firmware_patch = 0;

const size_t bnc_a_pin = 33;
const size_t bnc_b_pin = 32;

const size_t sd_card_cs_pin = 10;
const size_t sd_card_mosi_pin = 7;
const size_t sd_card_sck_pin = 14;

const char* const audio_ext_raw = ".RAW";
const char* const audio_ext_wav = ".WAV";
const char* const audio_exts[AUDIO_EXT_COUNT] = {audio_ext_raw, audio_ext_wav};

const char* const sd_prefix = "/SD/";

CONSTANT_STRING(device_name,"audio_controller");

// Fields
CONSTANT_STRING(volume_field_name,"volume");
const double volume_min = 0.0;
const double volume_max = 1.0;
const double volume_default = 0.25;

CONSTANT_STRING(trigger_frequency_left_field_name,"trigger_frequency_left");
const long trigger_frequency_left_min = 0;
const long trigger_frequency_left_max = 22000;
const long trigger_frequency_left_default = 6000;

CONSTANT_STRING(trigger_frequency_right_field_name,"trigger_frequency_right");
const long trigger_frequency_right_min = 0;
const long trigger_frequency_right_max = 22000;
const long trigger_frequency_right_default = 2000;

CONSTANT_STRING(trigger_duration_field_name,"trigger_duration");
const long trigger_duration_min = 0;
const long trigger_duration_max = 10000;
const long trigger_duration_default = 400;

// Parameters
CONSTANT_STRING(audio_path_parameter_name,"audio_path");

CONSTANT_STRING(percent_parameter_name,"percent");
const int percent_min = 0;
const int percent_max = 100;

CONSTANT_STRING(frequency_parameter_name,"frequency");
const int frequency_min = 0;
const int frequency_max = 22000;

// Methods
CONSTANT_STRING(get_sd_card_info_method_name,"getSDCardInfo");
CONSTANT_STRING(get_audio_paths_method_name,"getAudioPaths");
CONSTANT_STRING(play_path_method_name,"playPath");
CONSTANT_STRING(play_tone_method_name,"playTone");
CONSTANT_STRING(play_tone_left_method_name,"playToneLeft");
CONSTANT_STRING(play_tone_right_method_name,"playToneRight");
CONSTANT_STRING(play_noise_method_name,"playNoise");
CONSTANT_STRING(play_noise_left_method_name,"playNoiseLeft");
CONSTANT_STRING(play_noise_right_method_name,"playNoiseRight");
CONSTANT_STRING(stop_method_name,"stop");
CONSTANT_STRING(is_playing_method_name,"isPlaying");
CONSTANT_STRING(get_last_audio_path_played_method_name,"getLastAudioPathPlayed");
CONSTANT_STRING(get_position_method_name,"getPosition");
CONSTANT_STRING(get_length_method_name,"getLength");
CONSTANT_STRING(get_percent_complete_method_name,"getPercentComplete");

// Errors
}
