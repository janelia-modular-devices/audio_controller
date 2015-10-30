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
// modular_device.getParameterValue must be cast to either:
// const char*
// long
// double
// bool
// ArduinoJson::JsonArray&
// ArduinoJson::JsonObject&
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_device.getSavedVariableValue type must match the saved variable default type
// modular_device.setSavedVariableValue type must match the saved variable default type

void getSDCardInfoCallback()
{
  SDInterface& sd_interface = controller.getSDInterface();
  modular_device.addKeyToResponse("sd_card_info");
  modular_device.startResponseObject();
  modular_device.addToResponse("detected",sd_interface.getDetected());
  modular_device.addToResponse("type",sd_interface.getType());
  modular_device.addToResponse("formatted",sd_interface.getFormatted());
  modular_device.addToResponse("format",sd_interface.getFormat());
  modular_device.addToResponse("volume_size",sd_interface.getVolumeSize());
  modular_device.addToResponse("initialized",sd_interface.getInitialized());
  modular_device.stopResponseObject();
}

void addDirectoryToResponse(File dir, String pwd)
{
  while (true)
  {
    File entry =  dir.openNextFile();
    if (!entry)
    {
      // no more files
      break;
    }
    String full_path = pwd + String(entry.name());
    if (!entry.isDirectory())
    {
      modular_device.addToResponse(full_path);
    }
    else
    {
      addDirectoryToResponse(entry,full_path);
    }
    entry.close();
  }
}

void getSDCardAudioPathsCallback()
{
  File root = SD.open("/");
  modular_device.addKeyToResponse("audio_paths");
  modular_device.startResponseArray();
  addDirectoryToResponse(root,String("/"));
  modular_device.stopResponseArray();
}
}
