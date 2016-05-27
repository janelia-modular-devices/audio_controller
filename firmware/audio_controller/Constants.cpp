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

// Use semantic versioning http://semver.org/
const long firmware_major = 0;
const long firmware_minor = 1;
const long firmware_patch = 0;

HardwareSerial serial2(Serial2);

const size_t sd_card_cs_pin = 10;
const size_t sd_card_mosi_pin = 7;
const size_t sd_card_sck_pin = 14;

const char* const audio_ext_raw = ".RAW";
const char* const audio_ext_wav = ".WAV";
const char* const audio_exts[AUDIO_EXT_COUNT] = {audio_ext_raw, audio_ext_wav};

const char* const sd_prefix = "/SD/";

CONSTANT_STRING(device_name,"audio_controller");

// Fields

// Parameters
CONSTANT_STRING(audio_path_parameter_name,"audio_path");

CONSTANT_STRING(percent_parameter_name,"percent");
const int percent_min = 0;
const int percent_max = 100;

// Methods
CONSTANT_STRING(get_sd_card_info_method_name,"getSDCardInfo");
CONSTANT_STRING(get_audio_paths_method_name,"getAudioPaths");
CONSTANT_STRING(play_method_name,"play");
CONSTANT_STRING(stop_method_name,"stop");
CONSTANT_STRING(is_playing_method_name,"isPlaying");
CONSTANT_STRING(get_last_audio_path_played_method_name,"getLastAudioPathPlayed");
CONSTANT_STRING(set_volume_method_name,"setVolume");
CONSTANT_STRING(get_position_method_name,"getPosition");
CONSTANT_STRING(get_length_method_name,"getLength");
CONSTANT_STRING(get_percent_complete_method_name,"getPercentComplete");
CONSTANT_STRING(play_tone_method_name,"playTone");

// Errors
}
