/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:

#include <Servo.h>

Servo myservo;


int preVoltage = 5;
int count = 0;
int chairSpeed = 0;
bool brakePos = false;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(9);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  count++;
  if(preVoltage == 5 && voltage < 2.5) {
    preVoltage = 0;
  } else if (preVoltage == 0 && voltage > 2.5) {
    preVoltage = 5;
    chairSpeed = (chairSpeed + 2 * 314.159/(float)count) / 3;
    count = 0;
  }
  delay(10);
  if(count > 2000)
    chairSpeed = 0;
  // print out the value you read:
  Serial.println(chairSpeed);
  if(chairSpeed > 11.5 && !brakePos) {
    myservo.write(140);
    brakePos = true;
  } else if(brakePos && chairSpeed < 8.5){
    myservo.write(10);
    brakePos = false;
  }
}
