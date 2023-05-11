#include <Wire.h>

const int pingPin = 13;  // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12;  // Echo Pin of Ultrasonic Sensor
long duration, inches, cm;
int A = 9;  // dark green
int B = 5;  // red wire
int speed;
char input;  // to store input character received via BT.


void setup() {
  Serial.begin(9600);

  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  speed = analogRead(A0);
  speed = speed * 0.249;
  analogWrite(A, speed);
  analogWrite(B, speed);


  distance();
  if (cm > 40)  // check if there is no obstacle within 40 cm
  {
    // read input from Bluetooth module
    if (Serial.available()) {
      while (Serial.available()) {
        input = Serial.read();
        if (input == 'F') {
          forward();

        } else if (input == 'R') {
          right();


        } else if (input == 'L') {
          left();

        } else if (input == 'G') {
          backward();

        } else if (input == 'S') {
          stop();
        }
      }
    }
  } else if (cm <= 40)  // if there is an obstacle within 40 cm, stop the car
  {
    stop();
    delay(1000);
    backward();
    delay(800);
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void distance() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  delay(100);
}

void forward() {
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void stop() {
  digitalWrite(6, LOW);
  digitalWrite(4, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void backward() {
  digitalWrite(6, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void right() {
  digitalWrite(6, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void left() {
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}