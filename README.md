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
      "return":null
    },
    {
      "name":"setSerialNumber",
      "parameters":[
        {
          "name":"serial_number",
          "type":"long",
          "min":0,
          "max":65535
        }
      ],
      "return":null
    },
    {
      "name":"getSDCardInfo",
      "parameters":[],
      "return":null
    },
    {
      "name":"getAudioPaths",
      "parameters":[],
      "return":null
    },
    {
      "name":"playAudioPath",
      "parameters":[
        {
          "name":"path",
          "type":"string"
        }
      ],
      "return":null
    },
    {
      "name":"isPlaying",
      "parameters":[],
      "return":null
    },
    {
      "name":"getLastAudioPathPlayed",
      "parameters":[],
      "return":null
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
      "return":null
    }
  ],
  "status":"success"
}
```

