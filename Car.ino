#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIG_PIN A0  //trigger the ultrasonic sound pulses
#define ECHO_PIN A1  // produces a pulse from ultrasonic sensor
#define MAX_DISTANCE 200
#define MAX_SPEED 150  //motor speed
#define MAX_SPEED_OFFSET 20
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor motor1(1, MOTOR12_1KHZ);  // motor 1 connected at M1
AF_DCMotor motor2(3, MOTOR12_1KHZ);  // motor2 connected at M3
Servo myservo;                       //servo is named myservo
boolean goesForward = false;
int distance = 100;  //distance and speed int
int speedSet = 0;


void setup() {
  myservo.attach(9);   // Servo at digital pin 9
  myservo.write(115);  // servo at 115 degrees
  delay(2000);
  distance = readPing();  //distance from the sensor
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  // If distance is < 20 cm - do this function
  if (distance <= 20) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    if (distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}
int lookRight() {
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}
int lookLeft() {
  myservo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}
void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
void moveForward() {
  if (!goesForward) {  // moves forward if all clear
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}
void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
    delay(5);
  }
}
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
