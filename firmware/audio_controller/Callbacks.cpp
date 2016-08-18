// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"


namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_server.getParameterValue must be cast to either:
// const char*
// long
// double
// bool
// ArduinoJson::JsonArray&
// ArduinoJson::JsonObject&
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server.getFieldValue type must match the field default type
// modular_server.setFieldValue type must match the field default type
// modular_server.getFieldElementValue type must match the field array element default type
// modular_server.setFieldElementValue type must match the field array element default type

ModularDevice::ModularServer& modular_server = controller.getModularServer();

void getSDCardInfoCallback()
{
  SDInterface& sd_interface = controller.getSDInterface();
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseObject();
  modular_server.writeToResponse("detected",sd_interface.getDetected());
  modular_server.writeToResponse("type",sd_interface.getType());
  modular_server.writeToResponse("formatted",sd_interface.getFormatted());
  modular_server.writeToResponse("format",sd_interface.getFormat());
  modular_server.writeToResponse("volume_size",sd_interface.getVolumeSize());
  modular_server.writeToResponse("initialized",sd_interface.getInitialized());
  modular_server.endResponseObject();
}

void addDirectoryToResponse(File dir, const char *pwd)
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (!entry)
    {
      // no more files
      break;
    }
    char full_path[constants::STRING_LENGTH_PATH];
    full_path[0] = 0;
    strcat(full_path,pwd);
    strcat(full_path,entry.name());
    if (!entry.isDirectory())
    {
      bool audio_file = false;
      for (unsigned int i=0;i<constants::AUDIO_EXT_COUNT;++i)
      {
        if (strstr(full_path,constants::audio_exts[i]) != NULL)
        {
          audio_file = true;
        }
      }
      if (audio_file)
      {
        modular_server.writeToResponse(full_path);
      }
    }
    else
    {
      strcat(full_path,"/");
      addDirectoryToResponse(entry,full_path);
    }
    entry.close();
  }
}

void getAudioPathsCallback()
{
  File root = SD.open("/");
  modular_server.writeResultKeyToResponse();
  modular_server.beginResponseArray();
  addDirectoryToResponse(root,constants::sd_prefix);
  modular_server.endResponseArray();
}

void playPathCallback()
{
  if (!controller.codecEnabled())
  {
    modular_server.sendErrorResponse("No audio codec chip detected.");
    return;
  }
  const char* audio_path = modular_server.getParameterValue(constants::audio_path_parameter_name);
  if (!controller.isAudioPath(audio_path))
  {
    char err_msg[constants::STRING_LENGTH_ERROR_MESSAGE];
    err_msg[0] = 0;
    strcat(err_msg,"Invalid audio path: ");
    strcat(err_msg,audio_path);
    modular_server.sendErrorResponse(err_msg);
    return;
  }
  bool playing = controller.playPath(audio_path);
  if (!playing)
  {
    char err_msg[constants::STRING_LENGTH_ERROR_MESSAGE];
    err_msg[0] = 0;
    strcat(err_msg,"Unable to find audio path: ");
    strcat(err_msg,audio_path);
    modular_server.sendErrorResponse(err_msg);
  }
}

void playToneCallback()
{
  long frequency = modular_server.getParameterValue(constants::frequency_parameter_name);
  controller.playTone(frequency);
}

void stopCallback()
{
  controller.stop();
}

void isPlayingCallback()
{
  modular_server.writeResultToResponse(controller.isPlaying());
}

void getLastAudioPathPlayedCallback()
{
  modular_server.writeResultToResponse(controller.getLastAudioPathPlayed());
}

void getPositionCallback()
{
  modular_server.writeResultToResponse(controller.getPosition());
}

void getLengthCallback()
{
  modular_server.writeResultToResponse(controller.getLength());
}

void getPercentCompleteCallback()
{
  long position = controller.getPosition();
  long length = controller.getLength();
  long percent_complete = 100;
  if (length > 0)
  {
    percent_complete = (100*position)/length;
  }
  modular_server.writeResultToResponse(percent_complete);
}

// Field Callbacks
void setVolumeCallback()
{
  controller.updateVolume();
}

// EventController Callbacks
void stopEventCallback(int index)
{
  controller.stop();
}

void playToneEventCallback(int index)
{
  long frequency;
  bool bnc_a = digitalRead(constants::bnc_a_pin);
  if (bnc_a)
  {
    modular_server.getFieldValue(constants::trigger_frequency_high_field_name,frequency);
    controller.playTone(frequency);
  }
  else
  {
    modular_server.getFieldValue(constants::trigger_frequency_low_field_name,frequency);
    controller.playTone(frequency);
  }
  digitalWrite(13,HIGH);
}

// Interrupt Callbacks
void bncBInterruptCallback()
{
  int delay = 0;
  int period = 1000;
  int count = 1;
  int index = 0;
  long on_duration;
  modular_server.getFieldValue(constants::trigger_duration_field_name,on_duration);
  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(playToneEventCallback,
                                                                     stopEventCallback,
                                                                     delay,
                                                                     period,
                                                                     on_duration,
                                                                     count,
                                                                     index);
}

}
