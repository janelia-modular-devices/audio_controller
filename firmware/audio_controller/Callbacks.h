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
#include "ModularServer.h"
#include <SD.h>
#include "SDInterface.h"
#include "Constants.h"
#include "Controller.h"


namespace callbacks
{
void getSDCardInfoCallback();

void getAudioPathsCallback();

void playPathCallback();

void playToneCallback();

void stopCallback();

void isPlayingCallback();

void getLastAudioPathPlayedCallback();

void getPositionCallback();

void getLengthCallback();

void getPercentCompleteCallback();

// Field Callbacks
void setVolumeCallback();

}
#endif
