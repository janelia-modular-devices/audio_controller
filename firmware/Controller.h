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
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "ModularDevice.h"
#include "Constants.h"
#include "Callbacks.h"


class Controller
{
public:
  Controller();
  void setup();
  void update();

private:
  void playFile(const char* filename);
  AudioPlaySdWav play_wav_;
  // Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
  AudioOutputI2S audio_output_;
  //AudioOutputSPDIF audio_output_;
  //AudioOutputAnalog audio_output_;
  // AudioConnection patch_cord1_;
  // AudioConnection patch_cord2_;
  AudioControlSGTL5000 sgtl5000_1_;
};

extern Controller controller;

#endif
