
////////////////////////////////// Arm Up - Down Function /////////////////////////////////////////////////////
void armGo(uint8_t direct, uint8_t pwm) {
  if (direct == CW)
  {
    //digitalWrite(ARM_MOTOR_A2_PIN, LOW);
    digitalWrite(ARM_MOTOR_A1_PIN, HIGH);
  }
  else if (direct == CCW)
  {
    digitalWrite(ARM_MOTOR_B1_PIN, HIGH);
    // digitalWrite(ARM_MOTOR_A1_PIN, LOW);
  }
  else
  {
    digitalWrite(ARM_MOTOR_A1_PIN, LOW);
    digitalWrite(ARM_MOTOR_B1_PIN, LOW);
  }

  analogWrite(PWM_ARM_MOTOR, pwm);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// Arm Reset-Reposition /////////////////////////////////////////////////
void armReset(int up_rate, int servo_degree) {         // Move arm platform to zero position( Highest position )
  myservo.attach(SERVO_PIN);
  armGo(CCW, up_rate);
  while (1) {
    if (digitalRead(31) == LOW) {
      armGo(BRAKE, 150);
      break;
    }
  }
  for (int pos = 0; pos <= servo_degree; pos++) { // goes from 0 degrees to 180 degrees // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach(); // Optional
}

//////////////////////////////////////////// Grab Payload ////////////////////////////////////////////////////////////////////
void armGrab(int down_rate, int up_rate, int servo_degree) { // Grab payload from ground
  myservo.attach(SERVO_PIN);
  myservo.write(0);
  if (digitalRead(31) == HIGH) {
    armReset(150, 45);
  }

  armGo(CW, down_rate);
  while (1) {
    if (digitalRead(30) == LOW) {
      armGo(BRAKE, 150);
      break;
    }
  }

  for (int pos = 0; pos <= servo_degree; pos++) { // goes from 0 degrees to 180 degrees // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(servo_degree);

  armGo(CCW, up_rate);
  while (1) {
    if (digitalRead(31) == LOW) {
      armGo(BRAKE, 150);
      break;
    }
  }
  //myservo.detach(); // Optional

}

///////////////////////////////////////////// Release Arm ////////////////////////////////////////////////////////////////////
void armRelease(int down_rate, int up_rate, int servo_degree) { //Release payload to the ground and re-position arm
  myservo.attach(SERVO_PIN);
  myservo.write(servo_degree);// Optional


  armGo(CW, down_rate);
  while (1) {
    if (digitalRead(30) == LOW) {
      armGo(BRAKE, 150);
      break;
    }
  }

  for (int pos = servo_degree; pos >= 0; pos--) { // goes from 0 degrees to 180 degrees // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(0);

  armReset(150, 45);

}
