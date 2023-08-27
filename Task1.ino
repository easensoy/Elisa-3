/*
This Program is to make the robot follow a thick black line on white surface
*/

// A variable to store value read from ground sensor
int RawSensorValue; 

// array to store all ground sensor values
int ground[4] = {};

// Store left most sensor binary value
bool LeftMostSensor;

// Store front left sensor binary value
bool LeftSensor;

// Store front right sensor binary value
bool RightSensor;

// Store right most sensor binary value
bool RightMostSensor;

// Threshold value to distinguish between black and white surface,
// anything above 880 sensor value will be considered black and below 880 as white
  int Threshold_T1 = 880;

// Make enum containing 4 states of movement
enum WhereRobotNeedsToGo {Forward, Stop, Left, Right};

// Setting default movement state to Forward
enum WhereRobotNeedsToGo CurrentState = Forward;

// This function is being called from void loop() so it will run repeatedly  
void TASK_1() {
  
while(1)
{Serial.println("0");
  // First step is to update the sensor values by reading the sensors
  UpdateGroundSensorsT1();

  // ground array is filled with values of all sensors,
  // starting from ground[0] to ground[3] values are 
  // assigned to sensors from left to right i.e. 4 sensors
  LeftMostSensor = ground[0];
  LeftSensor = ground[1];
  RightSensor = ground[2];
  RightMostSensor = ground[3];

  // Now based on the sensor values we have to decide movement state of Robot
  // from Forward, LeftTurn and RightTurn
  ProcessRobotStateT1(LeftMostSensor, LeftSensor, RightSensor, RightMostSensor); //give us state
  
  // Once decision of movement is made, this function calls the respective movement codes
  ActOnRobotStateT1(); //left or right
 }
}  

// Updates values of all ground sensor and makes them binary based on threshol value. 
// Anything greater than threshold is 1 and lower than threshold is 0.
void UpdateGroundSensorsT1() {
  for (int i = 0; i<=3; i++) {
     ReadGroundSensorT1(i);
     ConvertSensorToBinaryT1(i);
  }
}

// Reads the Ground Sensor whose number is provided e.g 0, 1, 2 or 3
void ReadGroundSensorT1(int sensornum) {
  
// Turn on respective IR Led so that light shines on surface
// and we are able to read light coming back from ground.
  GroundLedOnT1(sensornum);
  delay(10);

 // Stores value received from analogReading the sensor in RawSensorValue Variable
 // Adding 8 to sensornumber as ground sensors are attached to pins 8,9,10 and 11
  RawSensorValue = analogRead(sensornum+8); //corresponding ground sensor
  
//  Serial.print(sensornum);
//  Serial.print("  ");
//  Serial.println(RawSensorValue);

// Turn off IR led after reading the sensor  
  GroundLedOffT1(sensornum);
  
}

// This function checks value in RawSensorValue Variable, if that is greater than Threshold value then ground sensors
// array's corresponding value is changed to 1, if not then it is given 0 value.
void ConvertSensorToBinaryT1(int sensornum) {
  if (RawSensorValue > Threshold_T1) {
    ground[sensornum] = 1;
  }
  else {
    ground[sensornum] = 0;
  }
  
}

// This function decides the movement of robot after checking values of all 4 ground sensors.
void ProcessRobotStateT1(bool LeftMostSensor, bool LeftSensor, bool RightSensor, bool RightMostSensor) {
  // if both left and right sensors are on black move straight
  if (RightMostSensor == 1 && LeftMostSensor == 1) {
    MotorsForwardT1();
  }
  // here if the right most sensor comes on black, the robot will keep moving right until left sensor comes on black
  else if (RightMostSensor == 1) {
//    CurrentState = Stop;
      do{
        RightTurnT1();
        }
        while(analogRead(9) < 880);
        LeftTurnT1();
  }

// if the left most sensor comes on black, the robot will keep moving left until right sensor comes on black  
  else if (LeftMostSensor == 1) {
//    CurrentState = Stop;
      do{
        LeftTurnT1();
        }
        while(analogRead(10) < 880);
        RightTurnT1();
  }

  // if both front sensors are on white move straight
  else if ((LeftSensor == 0) && (RightSensor == 0)) {
    CurrentState = Forward;
  }

  // if front left sensor is on black and front right on white move left
  else if ((LeftSensor == 1) && (RightSensor == 0)) {
    CurrentState = Left;
  }

  // if front left sensor is on white and front right on black move right
  else if ((LeftSensor == 0) && (RightSensor ==1)) {
    CurrentState = Right;
  }

  // in any other case also move forward
   else {
    CurrentState = Forward;
  }
}

// This function calls the respective movement functions based on current robot state
void ActOnRobotStateT1(){
  if (CurrentState == Forward) {
    MotorsForwardT1();
  }
  else if (CurrentState == Left) {
    LeftTurnT1();
  }
  else if (CurrentState ==Right) {
    RightTurnT1();
  }
  else if (CurrentState == Stop) {
    MotorsStopT1();
  }
}

// Turn Robot Left by moving Right wheel Forward
void LeftTurnT1() {
  LeftMotorForwardT1(0);
  RightMotorForwardT1(10);
}

// Turn Robot Right by moving Left wheel Forward
void RightTurnT1() {
  LeftMotorForwardT1(7);
  RightMotorForwardT1(0);
}

// Stop both wheels by giving no power to motors
void MotorsStopT1(){
  analogWrite(2,1);
  analogWrite(5,1);
  analogWrite(6,1);
  analogWrite(7,1);
}

// Function that makes Left wheel move Forward
void LeftMotorForwardT1(float duty) {
  analogWrite(6, duty * 2.55);
  analogWrite(7,0);
}

// Function that makes Right wheel move Forward
void RightMotorForwardT1(float duty) {
  analogWrite(5, duty *2.55);
  analogWrite(2,0);
}

// This function makes both wheels move Forward
void MotorsForwardT1() {
  LeftMotorForwardT1(7);
  RightMotorForwardT1(10);
}

// Turns the IR led off whose Index is provided
void GroundLedOffT1(unsigned char LedIndex) {
  if ((LedIndex ==0) |(LedIndex ==1) | (LedIndex ==2)| (LedIndex ==3)){
    PORTJ |= (1<<LedIndex);
  }
 }

// Turns the IR led on whose Index is provided
void GroundLedOnT1(unsigned char LedIndex) {
  if ((LedIndex ==0) |(LedIndex ==1) | (LedIndex ==2)| (LedIndex ==3)){
    PORTJ &= ~(1<<LedIndex);
  }
}
