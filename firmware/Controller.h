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
#include "ModularDevice.h"
#include "Constants.h"
#include "Callbacks.h"


class Controller
{
public:
  Controller();
  void setup();
  void update();
  SDInterface& getSDInterface();
private:
  SDInterface sd_interface_;
  void playFile(const char* filename);
};

extern Controller controller;

#endif
