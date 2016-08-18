// ----------------------------------------------------------------------------
// Controller.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>
#include "SDInterface.h"
#include "ModularServer.h"
#include "Constants.h"
#include "Callbacks.h"

#include "EventController.h"
#include "Streaming.h"


class Controller
{
public:
  Controller();
  void setup();
  void update();
  ModularDevice::ModularServer& getModularServer();

  SDInterface& getSDInterface();
  bool playPath(const char* path);
  void playTone(size_t frequency);
  void stop();
  bool isPlaying();
  const char* getLastAudioPathPlayed();
  long getPosition();
  long getLength();
  bool codecEnabled();
  bool isAudioPath(const char* path);
  void updateVolume();
private:
  ModularDevice::ModularServer modular_server_;

  ModularDevice::Field fields_[constants::FIELD_COUNT_MAX];
  ModularDevice::Parameter parameters_[constants::PARAMETER_COUNT_MAX];
  ModularDevice::Method methods_[constants::METHOD_COUNT_MAX];

  bool codec_enabled_;
  constants::audio_t audio_type_playing_;
  bool playing_;
  char path_played_[constants::STRING_LENGTH_PATH];
  SDInterface sd_interface_;
  void enableAudioCodec();
  void updatePlaying();
};

extern Controller controller;

#endif
