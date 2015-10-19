// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"


AudioPlaySdWav           play_wav;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S           audio_output;
//AudioOutputSPDIF       audio_output;
//AudioOutputAnalog      audio_output;
AudioConnection          patch_cord1(play_wav, 0, audio_output, 0);
AudioConnection          patch_cord2(play_wav, 1, audio_output, 1);
AudioControlSGTL5000     sgtl5000;

Controller::Controller()
{
}

void Controller::setup()
{
  // Audio Setup
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000.enable();
  sgtl5000.volume(0.5);

  // Setup SD Card
  sd_interface_.setup();

  // Pin Setup

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareNumber(constants::firmware_number);

  // Saved Variables

  // Parameters
  // ModularDevice::Parameter& duration_on_parameter = modular_device.createParameter(constants::duration_on_parameter_name);
  // duration_on_parameter.setUnits(constants::seconds_unit);
  // duration_on_parameter.setRange(constants::duration_min,constants::duration_max);
  // ModularDevice::Parameter& duration_off_parameter = modular_device.copyParameter(duration_on_parameter,constants::duration_off_parameter_name);
  // ModularDevice::Parameter& count_parameter = modular_device.createParameter(constants::count_parameter_name);
  // count_parameter.setRange(constants::count_min,constants::count_max);

  // Methods
  ModularDevice::Method& get_sd_card_info_method = modular_device.createMethod(constants::get_sd_card_info_method_name);
  get_sd_card_info_method.attachCallback(callbacks::getSDCardInfoCallback);

  ModularDevice::Method& get_sd_card_wav_paths_method = modular_device.createMethod(constants::get_sd_card_wav_paths_method_name);
  get_sd_card_wav_paths_method.attachCallback(callbacks::getSDCardWavPathsCallback);

  // ModularDevice::Method& get_led_pin_method = modular_device.createMethod(constants::get_led_pin_method_name);
  // get_led_pin_method.attachCallback(callbacks::getLedPinCallback);

  // ModularDevice::Method& blink_led_method = modular_device.createMethod(constants::blink_led_method_name);
  // blink_led_method.attachCallback(callbacks::blinkLedCallback);
  // blink_led_method.addParameter(duration_on_parameter);
  // blink_led_method.addParameter(duration_off_parameter);
  // blink_led_method.addParameter(count_parameter);

  // Start ModularDevice Server
  modular_device.startServer(constants::baudrate);
}

void Controller::update()
{
  modular_device.handleServerRequests();
  // playFile("SDTEST1.WAV");
  // delay(500);
  // playFile("SDTEST2.WAV");
  // delay(500);
  // playFile("SDTEST3.WAV");
  // delay(500);
  // playFile("SDTEST4.WAV");
  // delay(1500);
}

SDInterface& Controller::getSDInterface()
{
  return sd_interface_;
}

void Controller::playFile(const char *filename)
{
  // Serial.print("Playing file: ");
  // Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  play_wav.play(filename);

  // A brief delay for the library read WAV info
  // delay(5);

  // Simply wait for the file to finish playing.
  // while (play_wav.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
  //   float vol = analogRead(15);
  //   vol = vol / 1024;
  //   sgtl5000.volume(vol);
  // }
}

Controller controller;
