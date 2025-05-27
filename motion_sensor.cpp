#include "motion_sensor.h"  


int sensorInput = 2; // PIR sensor input pin

int sensorReturn = 0; // Variable to store PIR sensor output

void setup2() {
pinMode(sensorInput, INPUT); // Set sensor pin as input
pinMode(LED_BUILTIN, OUTPUT);
pinMode(A0, OUTPUT);
}

void loop2() {
sensorReturn = digitalRead(sensorInput); // Read input value from PIR sensor
// Check if motion is detected
if (sensorReturn == HIGH) {
digitalWrite(LED_BUILTIN, HIGH);
} else {
// Set cursor to the second row and print motion stopped message
digitalWrite(LED_BUILTIN, LOW);
}
}
