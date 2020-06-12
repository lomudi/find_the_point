#include <Arduino.h>
#include <Coordinates.h>
#include <Servo.h>
#include <PID_v1.h>

Servo servoOne;
Servo servoTwo;
int analogPin1 = A5;
int analogPin2 = A0;
int valAng;
int servoOneAngles[537];
int servoTwoAngles[537];

float *getFingerPoint(float r, float phi)
{
  // This method is doing coordinates conversion from polar, r = distance and phi = angle
  Coordinates point = Coordinates();
  point.fromPolar(r, phi);
  float myPoint[] = {point.getX(), point.getY()};
  return myPoint;
}

int stopFingerOne(int ang)
{
  if (ang >= 500)
  {
    servoOne.attach(8);
    servoOne.writeMicroseconds(0.5);
    servoOne.write(servoOneAngles[ang]);
    delay(1000);
  }
  else
  {
    servoOne.detach();
  }
}

int stopFingerTwo(int ang)
{
  if (ang >= 500)
  {
    servoTwo.attach(4);
    servoTwo.writeMicroseconds(0.5);
    servoTwo.write(servoTwoAngles[ang]);
    delay(1000);
  }
  else
  {
    servoTwo.detach();
  }
}

int initCalibrationOfServos()
{
  servoOne.attach(8);
  servoOne.write(0);
  servoTwo.attach(4);
  servoTwo.write(0);
  delay(150);

  for (size_t i = 536; i < 2418; i++)
  {
    servoOne.write(i);
    servoTwo.write(i);
    delay(150);
    
    int currAng1 = analogRead(analogPin1);
    int currAng2 = analogRead(analogPin2);
    
    servoOneAngles[currAng1] = i;
    Serial.print("save into servoOneAngles index: ");
    Serial.print(currAng1);
    Serial.print(" value = ");
    Serial.print(servoOneAngles[currAng1]);
    Serial.println("");

    servoTwoAngles[currAng2] = i;
    Serial.print("save into servoTwoAngles index: ");
    Serial.print(currAng2);
    Serial.print(" value = ");
    Serial.print(servoTwoAngles[currAng2]);
    Serial.println("");
  }
  servoOne.detach();
  servoTwo.detach();
}

void setup()
{
  Serial.begin(9600);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  initCalibrationOfServos();
}

void loop()
{
  int currAng1 = analogRead(analogPin1);
  int currAng2 = analogRead(analogPin2);
  stopFingerOne(currAng1);
  stopFingerTwo(currAng2);
}
