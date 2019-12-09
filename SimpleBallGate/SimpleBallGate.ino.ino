//I don't know that the pot knob works to adjust rate so I need to figure out a way to check that; but for now at least it will upload and function sooo 

#include <Arduino.h>
#include "SpeedyStepper.h"
//Stepper Motor definition
#define BG1_Stepper_Port 1

//Home Sensor definition
#define BG1_CamRotSensor 23

//Potentiometer definition
#define BG1_POT 7

#define INTERMITTENT_MIN 4000
#define INTERMITTENT_MAX 8000
#define POT_CHECK_TIME 1500
#define POT_ACCEPTED_DELTA 20

SpeedyStepper gateStepper;
// byte stepperPort; 
byte potPin = BG1_POT;
unsigned long potStartTime;
long potLastRead;
float readVal;
float rateVal;
long potVal, potHome;
long potMinVal = 0;
long potMaxVal = 0;

// potStartTime = millis();

//potMinVal = 0;
//potMaxVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // pinMode(55, OUTPUT);
  // pinMode(56, OUTPUT);
  pinMode(potPin, INPUT);
  gateStepper.connectToPort(1);
  gateStepper.setStepsPerRevolution(1036 * 8);
  gateStepper.setSpeedInRevolutionsPerSecond(.2);
  gateStepper.setAccelerationInRevolutionsPerSecondPerSecond(.5);
//  initializePot();
  gateStepper.enableStepper();
  homeGate();
  gateStepper.disableStepper();
  // Serial.println("Initial Homing Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  // homeGate();
  // Serial.println("Fake Homed");
  // gateStepper.enableStepper();
  // gateStepper.moveRelativeInSteps(90);
  // gateStepper.disableStepper();
  // Serial.println("Actually Homed");
  // digitalWrite(56, LOW);
  // delay(2000);
  // digitalWrite(56, HIGH);
//  checkPot();
  // Serial.println(readVal);
  gateStepper.enableStepper();
  gateStepper.moveRelativeInRevolutions(-.04);
  // gateStepper.disableStepper();
  // Serial.println("moved quarter");
  // gateStepper.enableStepper();
  homeGate(); //ball delivered at end
  gateStepper.disableStepper();
  // Serial.println("home");
  // delay(500);




}



void homeGate() {
  // digitalWrite(55, LOW);
  calculateRate();
  gateStepper.enableStepper();
  gateStepper.moveToHomeInRevolutions(-1, rateVal, 1, 23);
  gateStepper.disableStepper();
  // digitalWrite(55, HIGH);
}

void calculateRate() {
  if(readPot() < potMinVal) {
     initializePot();
  }
  pleaseWork();
}

/* void checkPot() {
//  if ((millis() - potStartTime) > POT_CHECK_TIME { 
    readVal = readPot();

    if (readVal < potMinVal) { 
      initializePot();
      return;
    }

    if (abs(readVal - potLastRead) < POT_ACCEPTED_DELTA) { 
      potVal = readVal;
    } else {
      potLastRead = readVal;
    }

    potStartTime = millis();
  }
 }
/* 
 *  
 */
void initializePot() {
  potHome = readPot();
  potMinVal = potHome;
  potMaxVal = potMinVal + 320;
}

void setPotMinVal(byte minVal) {
  potMinVal = minVal;
}

void setPotMaxVal(byte maxVal){
  potMaxVal = maxVal;
}

long readPot() {
  return analogRead(potPin);
}

void pleaseWork() { //convert readPot value into a decimal so that MoveToHomeInReovlutions can actually use the value
  readVal = readPot();
//  Serial.println("readVal: ");
//  Serial.println(readVal);
  rateVal = readVal/1000;
  Serial.println("rateVal: ");
  Serial.println(rateVal);
}
