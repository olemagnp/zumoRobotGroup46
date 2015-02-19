#include <PLab_ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>



#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors;

void setup() {
  // put your setup code here, to run once:
  sensors.init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.read(sensor_values);
  Serial.println(sensor_values[0]);
}
