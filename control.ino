#define HANDLE_TAGS
#include <SPI.h>
#include <SD.h>
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino uno
#include <TMRpcm.h>          // Library for audio play from SDcard
#include <stdio.h> // for random 
#include <stdlib.h> // for random 
#include <time.h> // for random
TMRpcm tmrpcm;  // Object to access library functions

File root;

int sensorInput = 4;  // PIR sensor input pin
int sensorReturn = 0;  // Variable to store PIR sensor output

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial) { ; }
  //Check card presence
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.print("no SD");
    return;
  }

  tmrpcm.speakerPin = 9;  //PWM pin 9 on Uno
  tmrpcm.setVolume(7);
  tmrpcm.loop(0);
  setup2();
}
void setup2() {
  pinMode(sensorInput, INPUT);  // Set sensor pin as input
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
}

void loop() {

  int r = rand() % 5 + 1; // generate a random number 
  // check if motion is detected 
  if (sensorReturn == HIGH) {
  String filename = String(r) + ".WAV"; // random number + .WAV extension (all files in folder must be named 1-5) 
  Serial.print("Playing " + filename + '\n');
  delay(1000); // delay before playing 
  tmrpcm.play(filename.c_str()); // play the file 

  }
  else {
    delay(1000); 
    Serial.print("No motion detected \n");
  }
  loop2();
}

void loop2() {
  sensorReturn = digitalRead(sensorInput);  // Read input value from PIR sensor
  // Check if motion is detected
  if (sensorReturn == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // Set cursor to the second row and print motion stopped message
    digitalWrite(LED_BUILTIN, LOW);
  }
}
