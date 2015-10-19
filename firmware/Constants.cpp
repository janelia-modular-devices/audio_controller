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
const int baudrate = 9600;

const int model_number = 1150;
const int firmware_number = 1;

const int sd_card_cs_pin = 10;
const int sd_card_mosi_pin = 7;
const int sd_card_sck_pin = 14;

// const double duration_min = 0.1;
// const double duration_max = 2.5;
// const long count_min = 1;
// const long count_max = 100;

CONSTANT_STRING(device_name,"audio_controller");
CONSTANT_STRING(get_sd_card_info_method_name,"getSDCardInfo");
CONSTANT_STRING(get_sd_card_wav_paths_method_name,"getSDCardWavPaths");
// CONSTANT_STRING(get_led_pin_method_name,"getLedPin");
// CONSTANT_STRING(blink_led_method_name,"blinkLed");
// CONSTANT_STRING(duration_on_parameter_name,"duration_on");
// CONSTANT_STRING(duration_off_parameter_name,"duration_off");
// CONSTANT_STRING(count_parameter_name,"count");
// CONSTANT_STRING(seconds_unit,"seconds");
}
