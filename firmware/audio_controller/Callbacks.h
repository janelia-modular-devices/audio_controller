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

void playToneLeftCallback();

void playToneRightCallback();

void playNoiseCallback();

void playNoiseLeftCallback();

void playNoiseRightCallback();

void stopCallback();

void isPlayingCallback();

void getLastAudioPathPlayedCallback();

void getPositionCallback();

void getLengthCallback();

void getPercentCompleteCallback();

// Field Callbacks
void setVolumeCallback();

// EventController Callbacks
void stopEventCallback(int index);

void playToneEventCallback(int index);

// Interrupt Callbacks
void bncBInterruptCallback();

}
#endif
