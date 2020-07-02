#include <Arduino.h>
#include <Coordinates.h>
#include <Servo.h>
#include <PID_v1.h>

Servo servoOne;
Servo servoTwo;
Servo servoThree;

int analogPin1 = A2;
int inputPin1 = 8;
int analogPin2 = A1;
int inputPin2 = 7;
int analogPin3 = A3;
int inputPin3 = 6;

int ledPin = 13;
int virtualLimitNum = 100;

float *getFingerPoint(float r, float phi)
{
  // This method is doing coordinates conversion from polar, r = distance and phi = angle
  Coordinates point = Coordinates();
  point.fromPolar(r, phi);
  float myPoint[] = {point.getX(), point.getY()};
  return myPoint;
}

int stopFingerOne(int virtualPoint1)
{
  int currAng1 = analogRead(analogPin1);

  if (virtualPoint1 <= virtualLimitNum)
  {
    int writeVal = map(virtualPoint1, 0, virtualLimitNum, 23, 183);
    servoOne.attach(inputPin1);
    servoOne.writeMicroseconds(0.5);
    servoOne.write(writeVal);
    delay(100);
  }
  else
  {
    servoOne.detach();
  }
}

int stopFingerTwo(int virtualPoint2)
{
  int currAng2 = analogRead(analogPin2);

  if (virtualPoint2 <= virtualLimitNum)
  {
    int writeVal = map(virtualPoint2, 0, virtualLimitNum, 23, 183);
    servoTwo.attach(inputPin2);
    servoTwo.writeMicroseconds(0.5);
    servoTwo.write(writeVal);
    delay(100);
  }
  else
  {
    servoTwo.detach();
  }
}

int stopFingerThree(int virtualPoint3)
{
  int currAng3 = analogRead(analogPin3);

  if (virtualPoint3 <= virtualLimitNum)
  {
    int writeVal = map(virtualPoint3, 0, virtualLimitNum, 23, 183);
    servoThree.attach(inputPin3);
    servoThree.writeMicroseconds(0.5);
    servoThree.write(writeVal);
    delay(100);
  }
  else
  {
    servoThree.detach();
  }
}

void handleUnityVirtualObject()
{
  if (Serial.available() > 0)
  {
    String incomingData = Serial.readStringUntil('\n');

    if (incomingData.startsWith("data"))
    {
      String mesg;
      int startPos = incomingData.indexOf(',');
      String Value = incomingData.substring(startPos + 1);
      startPos = Value.indexOf(',');
      String Value1 = Value.substring(0, startPos);
      Value = Value.substring(startPos + 1);
      startPos = Value.indexOf(',');
      String Value2 = Value.substring(0, startPos);
      String Value3 = Value.substring(startPos + 1);

      stopFingerOne(Value1.toInt());
      stopFingerTwo(Value2.toInt());
      stopFingerThree(Value3.toInt());

      // for testing
      if (Value1.toInt() == 10000 && Value2.toInt() == 10000 && Value3.toInt() == 10000)
      {
        for (int i = 0; i < 10; i++)
        {
          digitalWrite(ledPin, HIGH);
          delay(100);
          digitalWrite(ledPin, LOW);
          delay(100);
        }
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(analogPin3, INPUT);
}

void loop()
{
  handleUnityVirtualObject();  
}
