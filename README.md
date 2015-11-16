#audio_controller

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

##More Detailed Help on Installation and Usage

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

##Device Information

```json
{
  "method":"?",
  "device_info":{
    "name":"audio_controller",
    "model_number":1150,
    "serial_number":0,
    "firmware_version":{
      "major":0,
      "minor":1,
      "patch":0
    }
  },
  "methods":[
    "resetDefaults",
    "setSerialNumber",
    "getSDCardInfo",
    "getAudioPaths",
    "playAudioPath",
    "isPlaying",
    "getLastAudioPathPlayed",
    "setVolume"
  ],
  "status":"success"
}
```

##Verbose Device Information

```json
{
  "method":"??",
  "device_info":{
    "name":"audio_controller",
    "model_number":1150,
    "serial_number":0,
    "firmware_version":{
      "major":0,
      "minor":1,
      "patch":0
    }
  },
  "methods":[
    {
      "name":"resetDefaults",
      "parameters":[],
      "result_type":null
    },
    {
      "name":"setSerialNumber",
      "parameters":[],
      "result_type":null
    },
    {
      "name":"getSDCardInfo",
      "parameters":[],
      "result_type":"object"
    },
    {
      "name":"getAudioPaths",
      "parameters":[],
      "result_type":"array"
    },
    {
      "name":"playAudioPath",
      "parameters":[
        {
          "name":"path",
          "type":"string"
        }
      ],
      "result_type":null
    },
    {
      "name":"isPlaying",
      "parameters":[],
      "result_type":"bool"
    },
    {
      "name":"getLastAudioPathPlayed",
      "parameters":[],
      "result_type":"string"
    },
    {
      "name":"setVolume",
      "parameters":[
        {
          "name":"percent",
          "type":"long",
          "min":0,
          "max":100
        }
      ],
      "result_type":null
    }
  ],
  "status":"success"
}
```
