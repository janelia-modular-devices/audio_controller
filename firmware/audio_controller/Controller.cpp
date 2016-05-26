// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"


AudioPlaySdRaw g_play_sd_raw;
AudioPlaySdWav g_play_sd_wav;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S g_audio_output;
//AudioOutputSPDIF g_audio_output;
//AudioOutputAnalog g_audio_output;
AudioMixer4 mix0;
AudioMixer4 mix1;
AudioConnection g_patch_cord0(g_play_sd_raw, 0, mix0, 0);
AudioConnection g_patch_cord1(g_play_sd_wav, 0, mix0, 1);
AudioConnection g_patch_cord2(g_play_sd_raw, 1, mix1, 0);
AudioConnection g_patch_cord3(g_play_sd_wav, 1, mix1, 1);
AudioConnection g_patch_cord4(mix0, 0, g_audio_output, 0);
AudioConnection g_patch_cord5(mix1, 0, g_audio_output, 1);
AudioControlSGTL5000 g_sgtl5000;

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
  modular_server_.setName(constants::device_name);
  modular_server_.setModelNumber(constants::model_number);
  modular_server_.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  modular_server_.addServerStream(Serial);
  modular_server_.addServerStream(constants::serial2);

  // Set Storage
  modular_server_.setFieldStorage(fields_);
  modular_server_.setParameterStorage(parameters_);
  modular_server_.setMethodStorage(methods_);

  // Fields

  // Parameters
  ModularDevice::Parameter& audio_path_parameter = modular_server_.createParameter(constants::audio_path_parameter_name);
  audio_path_parameter.setTypeString();

  ModularDevice::Parameter& percent_parameter = modular_server_.createParameter(constants::percent_parameter_name);
  percent_parameter.setRange(constants::percent_min,constants::percent_max);

  // Methods
  ModularDevice::Method& get_sd_card_info_method = modular_server_.createMethod(constants::get_sd_card_info_method_name);
  get_sd_card_info_method.attachCallback(callbacks::getSDCardInfoCallback);
  get_sd_card_info_method.setReturnTypeObject();

  ModularDevice::Method& get_audio_paths_method = modular_server_.createMethod(constants::get_audio_paths_method_name);
  get_audio_paths_method.attachCallback(callbacks::getAudioPathsCallback);
  get_audio_paths_method.setReturnTypeArray();

  ModularDevice::Method& play_method = modular_server_.createMethod(constants::play_method_name);
  play_method.attachCallback(callbacks::playCallback);
  play_method.addParameter(audio_path_parameter);

  ModularDevice::Method& stop_method = modular_server_.createMethod(constants::stop_method_name);
  stop_method.attachCallback(callbacks::stopCallback);

  ModularDevice::Method& is_playing_method = modular_server_.createMethod(constants::is_playing_method_name);
  is_playing_method.attachCallback(callbacks::isPlayingCallback);
  is_playing_method.setReturnTypeBool();

  ModularDevice::Method& set_volume_method = modular_server_.createMethod(constants::set_volume_method_name);
  set_volume_method.attachCallback(callbacks::setVolumeCallback);
  set_volume_method.addParameter(percent_parameter);

  ModularDevice::Method& get_last_audio_path_played_method = modular_server_.createMethod(constants::get_last_audio_path_played_method_name);
  get_last_audio_path_played_method.attachCallback(callbacks::getLastAudioPathPlayedCallback);
  get_last_audio_path_played_method.setReturnTypeString();

  ModularDevice::Method& get_position_method = modular_server_.createMethod(constants::get_position_method_name);
  get_position_method.attachCallback(callbacks::getPositionCallback);
  get_position_method.setReturnTypeLong();

  ModularDevice::Method& get_length_method = modular_server_.createMethod(constants::get_length_method_name);
  get_length_method.attachCallback(callbacks::getLengthCallback);
  get_length_method.setReturnTypeLong();

  ModularDevice::Method& get_percent_complete_method = modular_server_.createMethod(constants::get_percent_complete_method_name);
  get_percent_complete_method.attachCallback(callbacks::getPercentCompleteCallback);
  get_percent_complete_method.setReturnTypeLong();

  // Setup Streams
  Serial.begin(constants::baudrate);
  constants::serial2.begin(constants::baudrate);

  // Start Modular Device Server
  modular_server_.startServer();
}

void Controller::update()
{
  modular_server_.handleServerRequests();
  updatePlaying();
}

ModularDevice::ModularServer& Controller::getModularServer()
{
  return modular_server_;
}

SDInterface& Controller::getSDInterface()
{
  return sd_interface_;
}

bool Controller::play(const char *path)
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

  stop();
  bool playing = false;

  char *raw_ext = strstr(path_upper,constants::audio_ext_raw);
  if (raw_ext != NULL)
  {
    file_type_playing_ = constants::RAW_TYPE;
    if (sd_specified)
    {
      playing = g_play_sd_raw.play(sd_path);
    }
  }

  if (!playing)
  {
    char *wav_ext = strstr(path_upper,constants::audio_ext_wav);
    if (wav_ext != NULL)
    {
      file_type_playing_ = constants::WAV_TYPE;
      if (sd_specified)
      {
        playing = g_play_sd_wav.play(sd_path);
      }
    }
  }

  playing_ = playing;
  if (playing)
  {
    path_played_[0] = 0;
    strcpy(path_played_,path_upper);
  }
  return playing;
}

void Controller::stop()
{
  switch (file_type_playing_)
  {
    case constants::RAW_TYPE:
      g_play_sd_raw.stop();
      break;
    case constants::WAV_TYPE:
      g_play_sd_wav.stop();
      break;
  }
  playing_ = false;
}

bool Controller::isPlaying()
{
  return playing_;
}

void Controller::setVolume(unsigned int percent)
{
  float volume = (float)percent/constants::percent_max;
  g_sgtl5000.volume(volume);
}

const char* Controller::getLastAudioPathPlayed()
{
  return path_played_;
}

long Controller::getPosition()
{
  long position = 0;
  switch (file_type_playing_)
  {
    case constants::RAW_TYPE:
      position = g_play_sd_raw.positionMillis();
      break;
    case constants::WAV_TYPE:
      position = g_play_sd_wav.positionMillis();
      break;
  }
  return position;
}

long Controller::getLength()
{
  long length = 0;
  switch (file_type_playing_)
  {
    case constants::RAW_TYPE:
      length = g_play_sd_raw.lengthMillis();
      break;
    case constants::WAV_TYPE:
      length = g_play_sd_wav.lengthMillis();
      break;
  }
  return length;
}

bool Controller::codecEnabled()
{
  return codec_enabled_;
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

void Controller::updatePlaying()
{
  switch (file_type_playing_)
  {
    case constants::RAW_TYPE:
      playing_ = g_play_sd_raw.isPlaying();
      break;
    case constants::WAV_TYPE:
      playing_ = g_play_sd_wav.isPlaying();
      break;
  }
}

Controller controller;
