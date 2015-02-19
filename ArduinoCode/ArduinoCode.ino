#include <QTRSensors.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <ZumoMotors.h>
#include <NewPing.h>
/*
Drive forward and turn left or right when border is detected
- Only reflectionsensor 0 and 5 are used.
*/


#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD 1600 //

// these might need to be tuned for different motor types
#define REVERSE_SPEED 200 // 0 is stopped, 400 is full speed
#define TURN_SPEED 200
#define FORWARD_SPEED 200
#define FAST_FORWARD_SPEED 400
#define REVERSE_LENGTH 10
#define TURN_DURATION 300 // ms
#define SERVO_PIN 11
#define PING_PIN_1 1
#define PING_PIN_2 3
#define PING_PIN_3 4
#define MAX_DIST 20

PLab_ZumoMotors motors;
ZumoMotors motors1;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

NewPing sonar(PING_PIN_1, PING_PIN_1, MAX_DIST), sonarR(PING_PIN_2, PING_PIN_2, MAX_DIST), sonarL(PING_PIN_3, PING_PIN_3, MAX_DIST);

#define NUM_SENSORS 6

//unsigned long servoTime;
unsigned int sensor_values[NUM_SENSORS];
//int servoState;   
ZumoReflectanceSensorArray sensors;

//Servo servo;

void setup()
{
  //servo.attach(SERVO_PIN);
  sensors.init();
  //servoTime = millis();
  //servoState = 2;
  //button.waitForButton();
}
void loop() {
  sensors.read(sensor_values);
  int time = sonar.ping();
  float dist = sonar.convert_cm(time);
  float distR = sonarR.ping_cm();
  float distL = sonarL.ping_cm();
  
  if (sensor_values[0] > QTR_THRESHOLD) {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.backward(REVERSE_SPEED, REVERSE_LENGTH);
    motors.turnRight(TURN_SPEED, 135);
  }
  else if (sensor_values[5] > QTR_THRESHOLD) {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.backward(REVERSE_SPEED, REVERSE_LENGTH);
    motors.turnLeft(TURN_SPEED, 135);
  }
  else if(dist != 0){
    motors1.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if(distR != 0){
    motors.turnRight(TURN_SPEED, 90);
  }
  else if(distL != 0){
    motors.turnLeft(TURN_SPEED, 90); 
  }
  else {
    motors1.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
//  if(servoTime + 50000 < millis()){
//      if(servoState == 1){
//        servo.write(90);
//        servoState = 2;
//      }
//      else{
//       servo.write(170);
//       servoState = 1;
//      }
//      servoTime = millis();
//    }
}

