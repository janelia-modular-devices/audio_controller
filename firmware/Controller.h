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

#include "Streaming.h"


class Controller
{
public:
  Controller();
  void setup();
  void update();
  SDInterface& getSDInterface();
  bool codecEnabled();
  bool isPlaying();
  const char* getLastAudioPathPlayed();
  bool isAudioPath(const char* path);
  bool playPath(const char* path);
  void setVolume(unsigned int percent);
private:
  bool codec_enabled_;
  bool playing_;
  char path_played_[constants::STRING_LENGTH_PATH];
  SDInterface sd_interface_;
  void enableAudioCodec();
  void updatePlaying();
};

extern Controller controller;

#endif
