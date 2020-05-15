#include <Arduino.h>
#include <Coordinates.h>

int ang = 1;
int dist = 10;

void getFingerPoint(float r, float phi) {
  Coordinates point = Coordinates();
  point.fromPolar(r,phi);
  Serial.println(point.getX());
  Serial.print(", ");
  Serial.println(point.getY());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  Serial.println("testing coordinates conversion from polar => ");
  getFingerPoint(dist, ang);
  delay(1000);
  Serial.print("\n\n\n");
  ang = ang + 3;
  dist = dist + 5;
} 
