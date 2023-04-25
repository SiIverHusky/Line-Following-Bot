/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  
  Group Member 1 (name & SID): HARIS Husnain 20921573
  Group Member 2 (name & SID): GOH Jinghann 20933992
  
*/

// assign meaningful names to those pins that will be used
const int pinL_Sensor = A5;      //pin A5: left sensor 
const int pinC_Sensor = A2;      //pin A2: central sensor
const int pinB_Sensor = A4;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

const int max_speed = 200;      //Speed of Motor

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int centralSensor = 0; // sensing white
int rightSensor = 1;   // not sensing white

int countBumper = 0;   // bumper sensor not triggered yet
int countStep = 0;

// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinC_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  
  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  analogWrite(pinL_PWM, 0);       //stop at the start position 
  analogWrite(pinR_PWM, 0);       //stop at the start position 
}

// the loop function runs over and over again forever

void loop() {

  // Arduino is reading the sensor measurements
  bumperSensor = digitalRead(pinB_Sensor);
  centralSensor = digitalRead(pinC_Sensor);  
  leftSensor = digitalRead(pinL_Sensor);
  rightSensor = digitalRead(pinR_Sensor);
  
  // car stops at the start position when bumper sensor no trigger
  if ( bumperSensor && countBumper == 0 ) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }

        //When detecting the end sign, go backwards and slow down 
  else if (!bumperSensor && countBumper == 1) {
      analogWrite(pinL_PWM, max_speed*0.6);
      analogWrite(pinR_PWM, max_speed*0.6);
      digitalWrite(pinL_DIR, 0);
      digitalWrite(pinR_DIR, 0);
      delay(200);
      countBumper = countBumper + 1;
      analogWrite(pinL_PWM, 0);
      analogWrite(pinR_PWM, 0);
      digitalWrite(pinL_DIR, 0);
      digitalWrite(pinR_DIR, 0);
      }  


  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinL_PWM, max_speed);
    analogWrite(pinR_PWM, max_speed);
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }

  // car is tracking on the white line
  else if ( bumperSensor && countBumper == 1) {
    // both on white so turn left  
    if (countStep == 0 && !leftSensor && !rightSensor && !centralSensor ) {
        analogWrite(pinL_PWM, max_speed*0.75);
        analogWrite(pinR_PWM, max_speed*0.75);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1); 
        countStep++;
        delay(200);
      } 

  // At connection between U and S
  //Should it be ==2 or ==1 because does initializing it count as 0-> 1 and first turn make it 1 -> 2? 
    if (countStep >= 1 && !leftSensor && !rightSensor && !centralSensor ){
      analogWrite(pinL_PWM, max_speed*0.75);
      analogWrite(pinR_PWM, max_speed*0.75);
      digitalWrite(pinL_DIR, 1);
      digitalWrite(pinR_DIR, 0); 
      countStep++;
      delay(200);
    }


    // Car as turned too much to the right, now turn left
    if ( !leftSensor && rightSensor ) {
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);  
      }
    // Car as turned too much to the left, now turn right 
    if ( leftSensor && !rightSensor ) {
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0);  
      }
    // go straight, dont turn
    if ( leftSensor && rightSensor ) {
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 1);  
      }
    
        // Car as turned too much to the left, now turn right 
    if ( leftSensor && !rightSensor && !centralSensor) {
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0);  
      }
      
    // Car as turned too much to the left, now turn right 
    if ( leftSensor && !rightSensor && !centralSensor) {
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);  
    }

  //Central sensor ensures car stays in straight line
  //Car too far left, turn right
    if (centralSensor && leftSensor && !rightSensor){
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0);  
      }
  //Car too far right, turn left 
    if (centralSensor && rightSensor && !leftSensor){
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);
      }



    
  }
}


// 1 means black
// 0 means white

//light on sensor on when detect white, means green light == 0 
//so when bumper sensor detects green light it becomes == 0 so equivalent command is !bumpersensor