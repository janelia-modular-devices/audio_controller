// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"


AudioPlaySdWav           g_play_sd_wav;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S           g_audio_output;
//AudioOutputSPDIF       g_audio_output;
//AudioOutputAnalog      g_audio_output;
AudioConnection          g_patch_cord1(g_play_sd_wav, 0, g_audio_output, 0);
AudioConnection          g_patch_cord2(g_play_sd_wav, 1, g_audio_output, 1);
AudioControlSGTL5000     g_sgtl5000;

Controller::Controller()
{
  codec_enabled_ = false;
  playing_ = false;
  path_played_[0] = 0;
}

void Controller::setup()
{
  // Audio Setup
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  enableAudioCodec();

  // Setup SD Card
  sd_interface_.setup();

  // Pin Setup

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Slave Serial
  // modular_device.addSlaveSerial(constants::slave_serial);

  // Saved Variables

  // Parameters
  ModularDevice::Parameter& path_parameter = modular_device.createParameter(constants::path_parameter_name);
  path_parameter.setTypeString();

  ModularDevice::Parameter& percent_parameter = modular_device.createParameter(constants::percent_parameter_name);
  percent_parameter.setRange(constants::percent_min,constants::percent_max);

  // Methods
  ModularDevice::Method& get_sd_card_info_method = modular_device.createMethod(constants::get_sd_card_info_method_name);
  get_sd_card_info_method.attachCallback(callbacks::getSDCardInfoCallback);
  get_sd_card_info_method.setReturnTypeObject();

  ModularDevice::Method& get_audio_paths_method = modular_device.createMethod(constants::get_audio_paths_method_name);
  get_audio_paths_method.attachCallback(callbacks::getAudioPathsCallback);
  get_audio_paths_method.setReturnTypeArray();

  ModularDevice::Method& play_audio_path_method = modular_device.createMethod(constants::play_audio_path_method_name);
  play_audio_path_method.attachCallback(callbacks::playAudioPathCallback);
  play_audio_path_method.addParameter(path_parameter);

  ModularDevice::Method& is_playing_method = modular_device.createMethod(constants::is_playing_method_name);
  is_playing_method.attachCallback(callbacks::isPlayingCallback);
  is_playing_method.setReturnTypeBool();

  ModularDevice::Method& get_last_audio_path_played_method = modular_device.createMethod(constants::get_last_audio_path_played_method_name);
  get_last_audio_path_played_method.attachCallback(callbacks::getLastAudioPathPlayedCallback);
  get_last_audio_path_played_method.setReturnTypeString();

  ModularDevice::Method& set_volume_method = modular_device.createMethod(constants::set_volume_method_name);
  set_volume_method.attachCallback(callbacks::setVolumeCallback);
  set_volume_method.addParameter(percent_parameter);

  // Start ModularDevice Server
  modular_device.startServer(constants::baudrate);
}

void Controller::update()
{
  modular_device.handleServerRequests();
  updatePlaying();
}

SDInterface& Controller::getSDInterface()
{
  return sd_interface_;
}

bool Controller::isAudioPath(const char *path)
{
  char path_upper[constants::STRING_LENGTH_PATH];
  String(path).toUpperCase().toCharArray(path_upper,constants::STRING_LENGTH_PATH);

  bool audio_path = false;
  for (unsigned int i=0;i<constants::AUDIO_EXT_COUNT;++i)
  {
    const char *audio_ext = constants::audio_exts[i];
    char *audio_ext_path = strstr(path_upper,audio_ext);
    if (audio_ext_path != NULL)
    {
      audio_path = true;
      break;
    }
  }
  return audio_path;
}

bool Controller::playPath(const char *path)
{
  char path_upper[constants::STRING_LENGTH_PATH];
  String(path).toUpperCase().toCharArray(path_upper,constants::STRING_LENGTH_PATH);

  bool sd_specified = false;
  char * sd_path;
  sd_path = strstr(path_upper,constants::sd_prefix);
  if (sd_path == path_upper)
  {
    sd_specified = true;
    // remove "/SD" from path
    sd_path = sd_path+strlen(constants::sd_prefix)-1;
  }

  // default to SD card if none specified
  if (!sd_specified)
  {
    sd_specified = true;
    sd_path = path_upper;
  }

  bool wav_path = false;
  char *wav_ext = strstr(path_upper,constants::audio_ext_wav);
  if (wav_ext != NULL)
  {
    wav_path = true;
  }

  bool playing = false;
  if (sd_specified && wav_path)
  {
    playing = g_play_sd_wav.play(sd_path);
  }
  playing_ = playing;
  if (playing)
  {
    path_played_[0] = 0;
    strcpy(path_played_,path_upper);
  }
  return playing;
}

void Controller::enableAudioCodec()
{
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  if (digitalRead(SDA) && digitalRead(SCL))
  {
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors so check first
    g_sgtl5000.enable();
    g_sgtl5000.volume(0.5);
    codec_enabled_ = true;
  }
}

bool Controller::codecEnabled()
{
  return codec_enabled_;
}

bool Controller::isPlaying()
{
  return playing_;
}

const char* Controller::getLastAudioPathPlayed()
{
  return path_played_;
}

void Controller::updatePlaying()
{
  playing_ = g_play_sd_wav.isPlaying();
}

void Controller::setVolume(unsigned int percent)
{
  float volume = (float)percent/constants::percent_max;
  g_sgtl5000.volume(volume);
}

Controller controller;
