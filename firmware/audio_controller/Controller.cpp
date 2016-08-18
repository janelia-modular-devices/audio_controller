// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"


// GUItool: begin automatically generated code
AudioSynthWaveformSine   g_sine;          //xy=295,345
AudioPlaySdWav           g_play_sd_wav;     //xy=300,238
AudioPlaySdRaw           g_play_sd_raw;     //xy=301,275
AudioMixer4              g_mixer1;         //xy=506,325
AudioMixer4              g_mixer2;         //xy=506,412
AudioMixer4              g_mixer0;         //xy=509,247
AudioOutputAnalog        g_dac;           //xy=698,412
AudioOutputI2S           g_i2s;           //xy=707,281
AudioConnection          patchCord1(g_sine, 0, g_mixer0, 2);
AudioConnection          patchCord2(g_sine, 0, g_mixer1, 2);
AudioConnection          patchCord3(g_sine, 0, g_mixer2, 3);
AudioConnection          patchCord4(g_play_sd_wav, 0, g_mixer0, 0);
AudioConnection          patchCord5(g_play_sd_wav, 0, g_mixer2, 0);
AudioConnection          patchCord6(g_play_sd_wav, 1, g_mixer1, 0);
AudioConnection          patchCord7(g_play_sd_wav, 1, g_mixer2, 1);
AudioConnection          patchCord8(g_play_sd_raw, 0, g_mixer0, 1);
AudioConnection          patchCord9(g_play_sd_raw, 0, g_mixer1, 1);
AudioConnection          patchCord10(g_play_sd_raw, 0, g_mixer2, 2);
AudioConnection          patchCord11(g_mixer1, 0, g_i2s, 1);
AudioConnection          patchCord12(g_mixer2, g_dac);
AudioConnection          patchCord13(g_mixer0, 0, g_i2s, 0);
AudioControlSGTL5000     g_sgtl5000;     //xy=507,175
// GUItool: end automatically generated code

Controller::Controller()
{
  codec_enabled_ = false;
  playing_ = false;
  path_played_[0] = 0;
}

void Controller::setup()
{
  EventController::event_controller.setup();

  // Audio Setup
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  enableAudioCodec();

  // Setup SD Card
  sd_interface_.setup();

  // Pin Setup
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  pinMode(constants::bnc_a_pin,INPUT_PULLUP);

  pinMode(constants::bnc_b_pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(constants::bnc_b_pin),callbacks::bncBInterruptCallback,FALLING);

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
  ModularDevice::Field& volume_field = modular_server_.createField(constants::volume_field_name,constants::volume_default);
  volume_field.setRange(constants::volume_min,constants::volume_max);
  volume_field.attachSetValueCallback(callbacks::setVolumeCallback);

  ModularDevice::Field& trigger_frequency_high_field = modular_server_.createField(constants::trigger_frequency_high_field_name,constants::trigger_frequency_high_default);
  trigger_frequency_high_field.setRange(constants::trigger_frequency_high_min,constants::trigger_frequency_high_max);

  ModularDevice::Field& trigger_frequency_low_field = modular_server_.createField(constants::trigger_frequency_low_field_name,constants::trigger_frequency_low_default);
  trigger_frequency_low_field.setRange(constants::trigger_frequency_low_min,constants::trigger_frequency_low_max);

  ModularDevice::Field& trigger_duration_field = modular_server_.createField(constants::trigger_duration_field_name,constants::trigger_duration_default);
  trigger_duration_field.setRange(constants::trigger_duration_min,constants::trigger_duration_max);

  // Parameters
  ModularDevice::Parameter& audio_path_parameter = modular_server_.createParameter(constants::audio_path_parameter_name);
  audio_path_parameter.setTypeString();

  ModularDevice::Parameter& percent_parameter = modular_server_.createParameter(constants::percent_parameter_name);
  percent_parameter.setRange(constants::percent_min,constants::percent_max);

  ModularDevice::Parameter& frequency_parameter = modular_server_.createParameter(constants::frequency_parameter_name);
  frequency_parameter.setRange(constants::frequency_min,constants::frequency_max);

  // Methods
  ModularDevice::Method& get_sd_card_info_method = modular_server_.createMethod(constants::get_sd_card_info_method_name);
  get_sd_card_info_method.attachCallback(callbacks::getSDCardInfoCallback);
  get_sd_card_info_method.setReturnTypeObject();

  ModularDevice::Method& get_audio_paths_method = modular_server_.createMethod(constants::get_audio_paths_method_name);
  get_audio_paths_method.attachCallback(callbacks::getAudioPathsCallback);
  get_audio_paths_method.setReturnTypeArray();

  ModularDevice::Method& play_path_method = modular_server_.createMethod(constants::play_path_method_name);
  play_path_method.attachCallback(callbacks::playPathCallback);
  play_path_method.addParameter(audio_path_parameter);

  ModularDevice::Method& stop_method = modular_server_.createMethod(constants::stop_method_name);
  stop_method.attachCallback(callbacks::stopCallback);

  ModularDevice::Method& is_playing_method = modular_server_.createMethod(constants::is_playing_method_name);
  is_playing_method.attachCallback(callbacks::isPlayingCallback);
  is_playing_method.setReturnTypeBool();

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

  ModularDevice::Method& play_tone_method = modular_server_.createMethod(constants::play_tone_method_name);
  play_tone_method.attachCallback(callbacks::playToneCallback);
  play_tone_method.addParameter(frequency_parameter);

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

  stop();
  bool playing = false;

  char *raw_ext = strstr(path_upper,constants::audio_ext_raw);
  if (raw_ext != NULL)
  {
    audio_type_playing_ = constants::RAW_TYPE;
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
      audio_type_playing_ = constants::WAV_TYPE;
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

void Controller::playTone(size_t frequency)
{
  stop();
  digitalWrite(13,HIGH);
  audio_type_playing_ = constants::TONE_TYPE;
  g_sine.amplitude(0);
  g_sine.frequency(frequency);
  g_sine.amplitude(1);
  updateVolume();
  playing_ = true;
}

void Controller::stop()
{
  digitalWrite(13,LOW);
  switch (audio_type_playing_)
  {
    case constants::RAW_TYPE:
      g_play_sd_raw.stop();
      break;
    case constants::WAV_TYPE:
      g_play_sd_wav.stop();
      break;
    case constants::TONE_TYPE:
      g_sine.amplitude(0);
  }
  playing_ = false;
}

bool Controller::isPlaying()
{
  return playing_;
}

const char* Controller::getLastAudioPathPlayed()
{
  return path_played_;
}

long Controller::getPosition()
{
  long position = 0;
  switch (audio_type_playing_)
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
  switch (audio_type_playing_)
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

void Controller::updateVolume()
{
  if (controller.codecEnabled())
  {
    double volume;
    modular_server_.getFieldValue(constants::volume_field_name,volume);
    g_sgtl5000.volume(volume);
  }
}

void Controller::enableAudioCodec()
{
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  if (digitalRead(SDA) && digitalRead(SCL))
  {
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors so check first
    codec_enabled_ = true;
    g_sgtl5000.enable();
    updateVolume();
  }
}

void Controller::updatePlaying()
{
  switch (audio_type_playing_)
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
