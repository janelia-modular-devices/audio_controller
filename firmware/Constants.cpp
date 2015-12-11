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
const int led_pin = 13;

const unsigned int baudrate = 9600;

const unsigned int model_number = 1150;

// Use semantic versioning http://semver.org/
const unsigned char firmware_major = 0;
const unsigned char firmware_minor = 1;
const unsigned char firmware_patch = 0;

HardwareSerial serial2(Serial2);

const unsigned int sd_card_cs_pin = 10;
const unsigned int sd_card_mosi_pin = 7;
const unsigned int sd_card_sck_pin = 14;

const char* const audio_ext_wav = ".WAV";
const char* const audio_ext_raw = ".RAW";
const char* const audio_exts[AUDIO_EXT_COUNT] = {audio_ext_wav,audio_ext_raw};

const char* const sd_prefix = "/SD/";

const int percent_min = 0;
const int percent_max = 100;

CONSTANT_STRING(device_name,"audio_controller");

CONSTANT_STRING(path_parameter_name,"path");
CONSTANT_STRING(percent_parameter_name,"percent");

CONSTANT_STRING(get_sd_card_info_method_name,"getSDCardInfo");
CONSTANT_STRING(get_audio_paths_method_name,"getAudioPaths");
CONSTANT_STRING(play_audio_path_method_name,"playAudioPath");
CONSTANT_STRING(is_playing_method_name,"isPlaying");
CONSTANT_STRING(get_last_audio_path_played_method_name,"getLastAudioPathPlayed");
CONSTANT_STRING(set_volume_method_name,"setVolume");
}
