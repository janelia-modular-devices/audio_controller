// ----------------------------------------------------------------------------
// Callbacks.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "ArduinoJson.h"
#include "ModularDevice.h"
#include <SD.h>
#include "SDInterface.h"
#include "Constants.h"
#include "Controller.h"


namespace callbacks
{
void getSDCardInfoCallback();

void getSDCardAudioPathsCallback();

// void getLedPinCallback();

// void blinkLedCallback();
}
#endif
