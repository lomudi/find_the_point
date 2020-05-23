#include <Arduino.h>
#include <Coordinates.h>
#include <Servo.h>
#include <PID_v1.h>

Servo fingerOne;
int analogPin = A5;
int valAng;

float *getFingerPoint(float r, float phi)
{
  // This method is doing coordinates conversion from polar, r = distance and phi = angle
  Coordinates point = Coordinates();
  point.fromPolar(r, phi);
  float myPoint[] = {point.getX(), point.getY()};
  return myPoint;
}

int stopFinger(float ang)
{
  if (ang >= 500)
  {
    fingerOne.attach(8);
    fingerOne.write(500);
  }
  else
  {
    fingerOne.detach();
  }
}

int servoCalibration()
{
  fingerOne.attach(8);
  for (size_t i = 0; i < 2400; i++)
  {
    fingerOne.write(i);
    delay(100);
    valAng = analogRead(analogPin);
    Serial.print(i);
    Serial.print(" ");
    Serial.print(valAng);
    Serial.println("");
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  servoCalibration();
}

void loop()
{
  // put your main code here, to run repeatedly:
  //valAng = analogRead(analogPin);
  //Serial.println(valAng);
  //stopFinger(valAng);
  delay(15); // waits for the servo to get there
}
