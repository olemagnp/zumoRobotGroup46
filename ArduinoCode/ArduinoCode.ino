#include <NewServo.h>
#include <QTRSensors.h>
#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <ZumoMotors.h>
#include <NewPing.h>

#define LED 13

// these might need to be tuned for different motor types
#define REVERSE_SPEED 200 // 0 is stopped, 400 is full speed
#define TURN_SPEED 200
#define FORWARD_SPEED 200
#define FAST_FORWARD_SPEED 400
#define REVERSE_LENGTH 10
#define TURN_DURATION 300 // ms
#define SERVO_PIN 5
#define PING_PIN_1 1
#define PING_PIN_2 3
#define PING_PIN_3 4
#define MAX_DIST 20
#define SERVO_STEP 2

PLab_ZumoMotors motors;
ZumoMotors motors1;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

NewPing sonar(PING_PIN_1, PING_PIN_1, MAX_DIST), sonarR(PING_PIN_2, PING_PIN_2, MAX_DIST), sonarL(PING_PIN_3, PING_PIN_3, MAX_DIST);
NewServo servo;
int servoDegs;
int servoStep;

#define NUM_SENSORS 6

unsigned int sensorTreshold;

//unsigned long servoTime;
unsigned int sensor_values[NUM_SENSORS];
//int servoState;   
ZumoReflectanceSensorArray sensors;

//Servo servo;

void setup()
{
  sensors.init();
  servo.attach(SERVO_PIN);
  Serial.begin(9600);
  servoDegs = 90;
  servoStep = SERVO_STEP;
}

void loop() {
  sensors.read(sensor_values);
  int time = sonar.ping();
  float dist = sonar.convert_cm(time);
  float distR = sonarR.ping_cm();
  float distL = sonarL.ping_cm();
  
  if (sensor_values[0] < 1000) {
    Serial.println("HEi2");
    // if leftmost sensor detects line, reverse and turn to the right
    motors.turnRight(TURN_SPEED, 80);
  }
  else if (sensor_values[6] < 1000) {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.turnLeft(TURN_SPEED, 80);
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
}
