
//Left Side
const int LEFT_PWM = 5;
const int LEFT_A = 4;
const int LEFT_B = 3;

//Right Side
const int RIGHT_PWM = 6;
const int RIGHT_A = 7;
const int RIGHT_B = 8;

void SetupMotors() {

  pinMode(LEFT_PWM, OUTPUT);
  pinMode(LEFT_A, OUTPUT);
  pinMode(LEFT_B, OUTPUT);

  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);

}

//Use this to test the motor directions
void TestTank(int motorSpeed) {

  Serial.println("FORWARD");
  LeftForward(motorSpeed);
  RightForward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("BACKWARD");
  LeftBackward(motorSpeed);
  RightBackward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("RIGHT");
  LeftBackward(motorSpeed);
  RightForward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("LEFT");
  LeftForward(motorSpeed);
  RightBackward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

}



//  If you are having issues with your Tank Bot's motor direction matching the
//  Controller Bot's joysticks, double check your wiring or try switching the HIGH and LOW values
//  in the digitalWrite() statements below.  

//                         !!WARNING!!
//   Never set a motor's A and B pins to HIGH at the same time!
//              !!WILL CAUSE MOTOR DRIVER FAILURE!!

void LeftForward(int motorSpeed) {

  analogWrite(LEFT_PWM, motorSpeed);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, HIGH);

}

void LeftBackward(int motorSpeed) {

  analogWrite(LEFT_PWM, motorSpeed);
  digitalWrite(LEFT_A, HIGH);
  digitalWrite(LEFT_B, LOW);

}

void LeftStop() {

  analogWrite(LEFT_PWM, 0);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, LOW);

}

void RightForward(int motorSpeed) {


  analogWrite(RIGHT_PWM, motorSpeed);
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, HIGH);

}

void RightBackward(int motorSpeed) {

  analogWrite(RIGHT_PWM, motorSpeed);
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);

}
void RightStop() {

  analogWrite(RIGHT_PWM, 0);
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, LOW);
}
