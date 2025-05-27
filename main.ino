#define HANDLE_TAGS
#include <SPI.h>
#include <SD.h>
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino uno
#include <TMRpcm.h>          // Library for audio play from SDcard
#include "motion_sensor.h"
TMRpcm tmrpcm;  // Object to access library functions
File root;
int wavs = 0;
int looping = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial){;}
  //Check card presence
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.print("no SD");
    return 1;
  }
  tmrpcm.speakerPin = 9;  //PWM pin 9 on Uno
  tmrpcm.setVolume(7);
  tmrpcm.loop(0);
  wavs = numberOfWavFiles(SD.open("/"));
  Serial.println(wavs);
  setup2();
}

void loop() {
  if (Serial.available()) {
    char wav = Serial.read();
    if (isdigit(wav)) {
      String filename = String(wav) + ".WAV";
      Serial.print("Playing " + filename + '\n');
      delay(1000);
      tmrpcm.play(filename.c_str());
      //while (tmrpcm.isPlaying())
      // ; // wait until it's done playing
    } else if (wav == 'L') {
      looping = !looping;
      tmrpcm.loop(looping);
      Serial.println(looping);
      Serial.println(looping ? "Looping" : "Not looping");
    }
  }
  loop2();
}

int numberOfWavFiles(File dir) {

  int wavFiles = 0;

  File entry = dir.openNextFile();
  while (entry) {
    String name = entry.name();
    if (name.endsWith(".WAV"))
      wavFiles++;
    entry.close();
    entry = dir.openNextFile();
  }
  return wavFiles;
}
