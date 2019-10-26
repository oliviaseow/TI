// Receives file size from python
// Calculates servo rotation amount 
// Rotates amount if emergency stop not pressed (if file size == 0, retracts)
// Watches for microphone input
// If microphone is blown, sends byte to python to delete contents

#include <Servo.h>

Servo flower;
int emergencystop = 4;

void setup() {
  Serial.begin(9600);
  pinMode(emergencystop, INPUT);
  Serial.println('ready');
}

void loop()
  {
  char inByte = ' ';
  
  if (digitalRead(emergencystop) == HIGH)
    {
      Serial.println('READY');
      
    if (Serial.available())
      {
      char inByte = Serial.read();
      Serial.println(inByte);
      
      // receive byte from python, maps to max, rotates amount
      flower.attach(9);
      flower.writeMicroseconds(1000); //1410
      delay(500);
      flower.detach();
  
      delay(2000);
  
      // watch for microphone sensor input
      // if microphone is blown, arduino sends byte back to python to delete contents
      }
  
    delay(100);
    }
  }
