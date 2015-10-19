// ----------------------------------------------------------------------------
// Callbacks.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Callbacks.h"

using namespace ArduinoJson::Parser;

namespace callbacks
{
// Callbacks must be non-blocking (avoid 'delay')
//
// modular_device.getParameterValue must be cast to either:
// char*
// long
// double
// bool
// JsonArray
// JsonObject
//
// For more info read about ArduinoJson v3 JsonParser JsonValues
//
// modular_device.getSavedVariableValue type must match the saved variable default type
// modular_device.setSavedVariableValue type must match the saved variable default type

void getSDCardInfoCallback()
{
  SDInterface& sd_interface = controller.getSDInterface();
  modular_device.addKeyToResponse("sd_card_info");
  modular_device.startResponseObject();
  modular_device.addBoolToResponse("detected",sd_interface.getDetected());
  modular_device.addToResponse("type",sd_interface.getType());
  modular_device.addBoolToResponse("formatted",sd_interface.getFormatted());
  modular_device.addToResponse("format",sd_interface.getFormat());
  modular_device.addToResponse("volume_size",sd_interface.getVolumeSize());
  modular_device.addBoolToResponse("initialized",sd_interface.getInitialized());
  modular_device.stopResponseObject();
}

void addDirectoryToResponse(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void lsCallback()
{
  File root = SD.open("/");
  printDirectory(root, 0);
}
}
