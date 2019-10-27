// Receives file size from python
// Calculates servo rotation amount
// Rotates amount if emergency stop not pressed (if file size == 0, retracts)
// Watches for microphone input
// If microphone is blown, sends byte to python to delete contents



#include <Servo.h>
Servo flower;
const long servo_off = 1500; // microsec
const long screw = servo_off + 36; // microsec
const long unscrew = servo_off - 90; // microsec

const long totalTime = 10 * 1E3; // 10 sec
const long totalSize = 360; // KB

const long biggestFile = 180; // KB
const long smallestFile = 70; // KB

long accumulator = 0;
long manual_control = 500;


void setup() {
    Serial.begin(115200);
    Serial.println("Starting...");
    flower.attach(9);
}


void handleSerial()
{
    if (Serial.available())
    {
        long fileSize = Serial.read();
        Serial.println(fileSize); // KB
        Serial.flush();

        if (fileSize > smallestFile && fileSize < biggestFile)
        {
            // rotate acoording to the file size
            long rotationTime = fileSize * totalTime / totalSize;
            accumulator += rotationTime;

            if (accumulator > totalTime) {
                Serial.println("folder overflow");
            } else {
                flower.writeMicroseconds(screw);
                delay(rotationTime);
            }
        } else if (fileSize == '0') {
            // go back to initial position
            reset();
        } else if (fileSize == '<') {               // screw manually
            // go back to initial position
            Serial.println("screwing");
            flower.writeMicroseconds(screw);
            delay(manual_control);
            accumulator += manual_control;
        } else if (fileSize == '>') {               // UNscrew manually
            // go back to initial position
            Serial.println("unscrewing");
            flower.writeMicroseconds(unscrew);
            delay(manual_control);
            accumulator = 0;
        } else {
            Serial.println("file size incorrect");
        }
        flower.writeMicroseconds(servo_off);
    }
}


    }


void reset() {
    // go back to initial position
    Serial.println("Reset");
    flower.writeMicroseconds(unscrew);
    delay(accumulator);
    accumulator = 0;
}


void loop()
{
    handleSerial();
}
