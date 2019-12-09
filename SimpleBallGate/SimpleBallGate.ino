#include <Arduino.h>
#include "SpeedyStepper.h"

//Stepper Motor definition
#define BG1_Stepper_Port 1

//Home Sensor definition
#define BG1_CamRotSensor 23

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  ballGate1.setupGateStepper();
  ballGate1.homeGate();
}

void loop() {
  // put your main code here, to run repeatedly:
  

}


void setupGateStepper() {
  this->gateStepper.connectToPort(this->stepperPort);
  this->gateStepper.setStepsPerRevolution(1036 * 8);
  this->gateStepper.setSpeedInRevolutionsPerSecond(.2);
  this->gateStepper.setAccelerationInRevolutionsPerSecondPerSecond(.5);
 
}

void homeGate() {
  this->gateStepper.enableStepper();
  this->gateStepper.moveToHomeInRevolutions(-1, .125, 1, this->gateHomeSensor);
  this->gateStepper.moveRelativeInRevolutions(-.01); //was .02 
  this->gateStepper.disableStepper();
}
