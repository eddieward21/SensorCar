#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define MAX_DISTANCE 200
#define MAX_SPEED 150
#define TRIG_PIN A0
#define ECHO_PIN A1

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE)
AF_DCMotor motor1(1, MOTOR12_KHZ)
AF_DCMotor motor2(3, MOTOR12_KHZ)

Servo myservo;
boolean goesForward = false;
int distance = 100;
int speedSet = 0;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing
  delay(100);


}

void loop() {
  // put your main code here, to run repeatedly:
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if(distance <= 20) {
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

    if(distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }

  }

}
