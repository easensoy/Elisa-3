/*
This Program is to make the robot follow a black line on white surface
*/

// Threshold value to distinguish between black and white surface, 
// anything above 880 sensor value will be considered black and below 880 as white
int Threshold_T2 = 880;

// This function is being called from void loop() so it will run repeatedly
void TASK_2() {

  // First step is to update the sensor values by reading the sensors
  UpdateGroundSensors_T2();

  // ground array is filled with values of all sensors,
  // starting from ground[0] to ground[3] values are 
  // assigned to sensors from left to right i.e. 4 sensors
  LeftMostSensor = ground[0];
  LeftSensor = ground[1];
  RightSensor = ground[2];
  RightMostSensor = ground[3];

  // Now based on the sensor values we have to decide movement state of Robot
  // from Forward, LeftTurn and RightTurn
  ProcessRobotState_T2(LeftMostSensor, LeftSensor, RightSensor, RightMostSensor); //give us state

  // Once decision of movement is made, this function calls the respective movement codes
  ActOnRobotState_T2(); //left or right

}

// Updates values of all ground sensors and makes them binary based on threshold value. 
// Anything greater than threshold is 1 and lower than threshold is 0.
void UpdateGroundSensors_T2() {
  for (int i = 0; i<=3; i++) {
     ReadGroundSensor_T2(i);
     ConvertSensorToBinary_T2(i);
  }
}

// Reads the Ground Sensor whose number is provided e.g 0, 1, 2 or 3
void ReadGroundSensor_T2(int sensornum) {
  // Turn on respective IR Led so that light shines on surface and we are able to read light coming back from ground.
  GroundLedOn_T2(sensornum);
  delay(10);
  
  // Stores value received from analogReading the sensor in RawSensorValue Variable
  // Adding 8 to sensornumber as ground sensors are attached to pins 8,9,10 and 11
  RawSensorValue = analogRead(sensornum+8); //corresponding ground sensor
  
//  Serial.print(sensornum);
//  Serial.print("  ");
//  Serial.println(RawSensorValue);

  // Turn off IR led after reading the sensor
  GroundLedOff_T2(sensornum);
  
}

// This function checks value in RawSensorValue Variable, if that is greater than Threshold value then ground sensors
// array's corresponding value is changed to 1, if not then it is given 0 value.
void ConvertSensorToBinary_T2(int sensornum) {
  if (RawSensorValue > Threshold_T2) {
    ground[sensornum] = 1;
  }
  else {
    ground[sensornum] = 0;
  }
  
}

// This function decides the movement of robot after checking values of all 4 ground sensors.
void ProcessRobotState_T2(bool LeftMostSensor, bool LeftSensor, bool RightSensor, bool RightMostSensor) {
  // here if the right most sensor comes on black, the robot will keep moving right until left sensor comes on black
  if (RightMostSensor == 1) {
//    CurrentState = Stop;
      do{
        RightTurn_T2();
        }
        while(analogRead(8) < 880);
        LeftTurn_T2();
  }

  // if the left most sensor comes on black, the robot will keep moving left until right sensor comes on black
  else if (LeftMostSensor == 1) {
//    CurrentState = Stop;
      do{
        LeftTurn_T2();
        }
        while(analogRead(11) < 880);
        RightTurn_T2();
  }

  // if both front sensors are on white move straight
  else if ((LeftSensor == 0) && (RightSensor == 0)) {
    CurrentState = Forward;
  }

  // if front left sensor is on black and front right on white change current state to Left
  else if ((LeftSensor == 1) && (RightSensor == 0)) {
    CurrentState = Left;
  }

  // if front left sensor is on white and front right on black change current state to Right
  else if ((LeftSensor == 0) && (RightSensor ==1)) {
    CurrentState = Right;
  }

  // in any other case also change current state to Forward
   else {
    CurrentState = Forward;
  }
}

// This function calls the respective movement functions based on current robot state
void ActOnRobotState_T2(){
  if (CurrentState == Forward) {
    MotorsForward_T2();
  }
  else if (CurrentState == Left) {
    LeftTurn_T2();
  }
  else if (CurrentState ==Right) {
    RightTurn_T2();
  }
  else if (CurrentState == Stop) {
    MotorsStop_T2();
  }
}

// Turn Robot Left by moving Right wheel Forward and Left wheel backward.
void LeftTurn_T2() {
  analogWrite(6, 0);
  analogWrite(7, 6.7 * 2.55);
  RightMotorForward_T2(9);
}

// Turn Robot Right by moving Left wheel Forward and Right wheel backward
void RightTurn_T2() {
  LeftMotorForward_T2(7.5);
  analogWrite(5, 0);
  analogWrite(2, 10 * 2.55);
}

// Stop both wheels by giving no power to motors
void MotorsStop_T2(){
  analogWrite(2,1);
  analogWrite(5,1);
  analogWrite(6,1);
  analogWrite(7,1);
}

// Function that makes Left wheel move Forward
void LeftMotorForward_T2(float duty) {
  analogWrite(6, duty * 2.55);
  analogWrite(7,0);
}

// Function that makes Right wheel move Forward
void RightMotorForward_T2(float duty) {
  analogWrite(5, duty *2.55);
  analogWrite(2,0);
}

// This function makes both wheels move Forward
void MotorsForward_T2() {
  LeftMotorForward_T2(6.5);
  RightMotorForward_T2(9.5);
}

// Turns the IR led off whose Index is provided
void GroundLedOff_T2(unsigned char LedIndex) {
  if ((LedIndex ==0) |(LedIndex ==1) | (LedIndex ==2)| (LedIndex ==3)){
    PORTJ |= (1<<LedIndex);
  }
 }

// Turns the IR led on whose Index is provided 
void GroundLedOn_T2(unsigned char LedIndex) {
  if ((LedIndex ==0) |(LedIndex ==1) | (LedIndex ==2)| (LedIndex ==3)){
    PORTJ &= ~(1<<LedIndex);
  }
 }
