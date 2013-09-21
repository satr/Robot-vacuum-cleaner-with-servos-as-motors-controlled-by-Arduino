// This example code is in the public domain.

#include <Servo.h> 
 
//Pins where servos are connected
int pinLeftServo = 9;
int pinRightServo = 10;
//Pins where bumpers are connected
int pinLeftBumper = 6;
int pinRightBumper = 7;
//Pin for LED
int pinLED = 13;

// create servo object to control a left servo 
Servo rightServo, leftServo;
//middle position when servo does not rotate
int stopPosLeftServo = 91;
int stopPosRightServo = 85;
//addition to position value when servo rotates in front direction of the robot
int movePosLeftServo = 5;
int movePosRightServo = -5;
//rotation direction
const boolean ForwardDirection = true;
const boolean BackwardDirection = false;
//how long (in msec) robot turns left or right when bumper gets pressed
const int TurningDelay = 1000;


//---- initialization
void setup() 
{ 
  // attaches the servos on pins 9 to the servo objects 
  rightServo.attach(pinLeftServo); 
  leftServo.attach(pinRightServo); 
  //setup pin for LED
  pinMode(pinLED, OUTPUT);
  //setup pins for bumpers
  //these inputs are pulled up to power (over a resistor) 
  //so that by default they have high level ("1" or "true")
  //if ground is connected to this input - it gets a low level ("0" or "false")
  pinMode(pinLeftBumper, INPUT_PULLUP);
  pinMode(pinRightBumper, INPUT_PULLUP);

  //start servo running
  runLeftServo(ForwardDirection);
  runRightServo(ForwardDirection);
}

//---- main loop
void loop() 
{ 
  turnLedOnWhen(checkLeftBumperPressed() || checkRightBumperPressed());
  
  if(checkLeftBumperPressed()){
      runLeftServo(BackwardDirection);
      delay(TurningDelay);
      runLeftServo(ForwardDirection);
  }

  turnLedOnWhen(checkLeftBumperPressed() || checkRightBumperPressed());

  if(checkRightBumperPressed()){
      runRightServo(BackwardDirection);
      delay(TurningDelay);
      runRightServo(ForwardDirection);
  }

  delay(20);
} 

//---- methods

void turnLedOnWhen(boolean ledState){
  digitalWrite(pinLED, ledState);
}

boolean checkLeftBumperPressed(){
  return !digitalRead(pinLeftBumper);
}

boolean checkRightBumperPressed(){
  return !digitalRead(pinRightBumper);
}

void runLeftServo(boolean runDirection){
  runServo(leftServo, 
           stopPosLeftServo, 
           runDirection? movePosLeftServo: -movePosLeftServo);
}

void runRightServo(boolean runDirection){
  runServo(rightServo, 
           stopPosRightServo, 
           runDirection? movePosRightServo: (-1 * movePosRightServo));
}

void runServo(Servo servo, int stopPos, int movePos){
  servo.write(stopPos + movePos);
}

