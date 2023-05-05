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

const int max_speed = 205;      //Speed of Motor

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int centralSensor = 0; // sensing white
int rightSensor = 1;   // not sensing white

int countBumper = 0;   // bumper sensor not triggered yet
int countStep = 0;
int flagStraight = 1;

// center sensor == 1 i.e. center is off track
void straighten(){
    if (leftSensor && !rightSensor){
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 1);
        digitalWrite(pinR_DIR, 0);
    }
    if (!leftSensor && rightSensor){
        analogWrite(pinL_PWM, max_speed);
        analogWrite(pinR_PWM, max_speed);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, 1);
    }
}

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

  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinL_PWM, max_speed);
    analogWrite(pinR_PWM, max_speed);
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }

  //When detecting the end sign, go backwards and slow down  
  else if (!bumperSensor && countBumper == 1) {
      analogWrite(pinL_PWM, max_speed*0.6);
      analogWrite(pinR_PWM, max_speed*0.6);
      digitalWrite(pinL_DIR, 0);
      digitalWrite(pinR_DIR, 0);
      delay(50);
      analogWrite(pinL_PWM, max_speed);
      analogWrite(pinR_PWM, max_speed);
      countBumper = countBumper + 1;
      delay(450);
      analogWrite(pinL_PWM, 0);
      analogWrite(pinR_PWM, 0);
      digitalWrite(pinL_DIR, 0);
      digitalWrite(pinR_DIR, 0);
      }  
    // car is tracking on the white line
    else if (bumperSensor && countBumper == 1){
        if (centralSensor && flagStraight){  //Center Sensor is on black, so harsh straighten
            straighten();
        }
        else if (countStep == 0 && !leftSensor && !rightSensor) { //T junction, go left
            analogWrite(pinL_PWM, max_speed*0.65);
            analogWrite(pinR_PWM, max_speed*0.65);
            digitalWrite(pinL_DIR, 0);
            digitalWrite(pinR_DIR, 1); 
            countStep++;
            delay(350);
        }
        else if (countStep > 0 && !leftSensor && !rightSensor){ //US connection, go right
            analogWrite(pinL_PWM, max_speed*0.75);
            analogWrite(pinR_PWM, max_speed*0.75);
            digitalWrite(pinL_DIR, 1);
            digitalWrite(pinR_DIR, 0); 
            countStep++;
            flagStraight = 0;
            delay(200);
        }
        else if(!leftSensor && rightSensor){ //left sensor is on white, so turn left
            analogWrite(pinL_PWM, max_speed);
            analogWrite(pinR_PWM, max_speed);
            digitalWrite(pinL_DIR, 0);
            digitalWrite(pinR_DIR, 1);
        }
        else if (leftSensor && !rightSensor){ //right sensor is on white, so turn right
            analogWrite(pinL_PWM, max_speed);
            analogWrite(pinR_PWM, max_speed);
            digitalWrite(pinL_DIR, 1);
            digitalWrite(pinR_DIR, 0);
        }
        else if (leftSensor && rightSensor){ //both are on black, so go straight
            analogWrite(pinL_PWM, max_speed);
            analogWrite(pinR_PWM, max_speed);
            digitalWrite(pinL_DIR, 1);
            digitalWrite(pinR_DIR, 1);
        }
    }   
  }


// 1 means black
// 0 means white
// !bumpersensor means detect
// bumpersensor means dont detect