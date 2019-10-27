// Receives file size from python
// Calculates servo rotation amount
// Rotates amount if emergency stop not pressed (if file size == 0, retracts)
// Watches for microphone input
// If microphone is blown, sends byte to python to delete contents



#include <Servo.h>
Servo flower;
const long servo_on = 1410; // microsec
const long servo_off = 1500; // microsec

const long totalTime = 10 * 1E3; // 10 sec
const long totalSize = 360; // KB

const long biggestFile = 180; // KB
const long smallestFile = 70; // KB

long accumulator = 0;


void setup() {
    Serial.begin(115200);
    Serial.println("Starting...");
    flower.attach(9);
}


void loop()
{
    if (Serial.available())
    {
        long fileSize = Serial.read();
        Serial.println(fileSize); // KB
        Serial.flush();

        if (fileSize < smallestFile || fileSize > biggestFile) {
            Serial.println("file is too small or too big");
        } else {
            long rotationTime = fileSize * totalTime / totalSize;
            accumulator += rotationTime;

            if (accumulator > totalTime) {
                Serial.println("folder overflow");
            } else {
                flower.writeMicroseconds(servo_on);
                delay(rotationTime);
                flower.writeMicroseconds(servo_off);
            }
        }

        // watch for microphone sensor input
        // if microphone is blown, arduino sends byte back to python to delete contents
    }

    delay(50);
}
