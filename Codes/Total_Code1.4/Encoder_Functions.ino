
////////////////////////////// Encoder interrupt Handlers ////////////////////////////////////////////////////////////////////////
void leftEncoderEvent() {
  leftCount++;
}
void rightEncoderEvent() {
  rightCount++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// PID Go Straight ///////////////////////////////////////////////////////////////////////////////
void goStraight(int goDistance) { ///// Distance in Millimeters
  leftCount = 0;
  rightCount = 0;
  float encCount = (goDistance * 220.0) / (3.0 * 65.0);
  int strt = rightCount;
  attachInterrupt(digitalPinToInterrupt(RM_ENCODER_A), leftEncoderEvent, RISING);
  attachInterrupt(digitalPinToInterrupt(LM_ENCODER_A), rightEncoderEvent, RISING);
  normalPWM + 0;
  while (normalPWM < 150) {
    normalPWM += 10;
    motorGo(MOTOR_2, CW, normalPWM);     //left motor
    motorGo(MOTOR_1, CW, normalPWM + 7);  //right motor
    delay(50);
  }
  //motorGo(MOTOR_1, CW, 80 + 7);  //right motor
  //delay(dly);
  //motorGo(MOTOR_2, CW, 80);     //left motor

  while (1) {
    //    while (normalPWM < 150) {
    //      normalPWM += 10;
    //      motorGo(MOTOR_2, CW, normalPWM);     //left motor
    //      motorGo(MOTOR_1, CW, normalPWM + 7);  //right motor
    //      delay(100);
    //    }
    normalPWM = 150;
    error = leftCount - rightCount;
    addPWM = round(kp * error + ki * errorSum + kd * lastError);
    lastError = error;
    errorSum += error;

    motorGo(MOTOR_2, CW, constrain(normalPWM - addPWM - 17 , 0, 255));   //left motor
    motorGo(MOTOR_1, CW, constrain(normalPWM + addPWM + 10, 0, 255));  //right motor

    //    Serial.print("Right : ");
    //    Serial.println(constrain(normalPWM + addPWM, 0, 255));
    //    Serial.print("Left : ");
    //    Serial.println(constrain(normalPWM - addPWM, 0, 255));
    //    Serial.println(encCount);
    //    Serial.println(rightCount);

    if (rightCount >=  strt + encCount) {
      motorGo(MOTOR_1, CCW, 255);
      motorGo(MOTOR_2, CCW, 255);
      delay(10);
      motorGo(MOTOR_1, BRAKE, 255);
      motorGo(MOTOR_2, BRAKE, 255);
      delay(20);
      motorGo(MOTOR_1, BRAKE, 0);
      motorGo(MOTOR_2, BRAKE, 0);
      detachInterrupt(digitalPinToInterrupt(RM_ENCODER_A));
      detachInterrupt(digitalPinToInterrupt(LM_ENCODER_A));
      break;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void goStraightBack(int goDistance) { ///// Distance in Millimeters
  leftCount = 0;
  rightCount = 0;
  float encCount = (goDistance * 220.0) / (3.0 * 65.0);
  int strt = rightCount;
  attachInterrupt(digitalPinToInterrupt(RM_ENCODER_A), leftEncoderEvent, RISING);
  attachInterrupt(digitalPinToInterrupt(LM_ENCODER_A), rightEncoderEvent, RISING);
  normalPWM + 0;
  while (normalPWM < 150) {
    normalPWM += 10;
    motorGo(MOTOR_2, CCW, normalPWM);     //left motor
    motorGo(MOTOR_1, CCW, normalPWM-7 );  //right motor
    delay(20);
  }
  //motorGo(MOTOR_1, CW, 80 + 7);  //right motor
  //delay(dly);
  //motorGo(MOTOR_2, CW, 80);     //left motor

  while (1) {
    //    while (normalPWM < 150) {
    //      normalPWM += 10;
    //      motorGo(MOTOR_2, CW, normalPWM);     //left motor
    //      motorGo(MOTOR_1, CW, normalPWM + 7);  //right motor
    //      delay(100);
    //    }
    normalPWM = 150;
    error = leftCount - rightCount;
    addPWM = round(kp * error + ki * errorSum + kd * lastError);
    lastError = error;
    errorSum += error;

    motorGo(MOTOR_2, CCW, constrain(normalPWM - addPWM  , 0, 255));   //left motor
    motorGo(MOTOR_1, CCW, constrain(normalPWM + addPWM , 0, 255));  //right motor

    //    Serial.print("Right : ");
    //    Serial.println(constrain(normalPWM + addPWM, 0, 255));
    //    Serial.print("Left : ");
    //    Serial.println(constrain(normalPWM - addPWM, 0, 255));
    //    Serial.println(encCount);
    //    Serial.println(rightCount);

    if (rightCount >=  strt + encCount) {
      motorGo(MOTOR_1, CW, 255);
      motorGo(MOTOR_2, CW, 255);
      delay(10);
      motorGo(MOTOR_1, BRAKE, 255);
      motorGo(MOTOR_2, BRAKE, 255);
      delay(20);
      motorGo(MOTOR_1, BRAKE, 0);
      motorGo(MOTOR_2, BRAKE, 0);
      detachInterrupt(digitalPinToInterrupt(RM_ENCODER_A));
      detachInterrupt(digitalPinToInterrupt(LM_ENCODER_A));
      break;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rotateTo(int rot_angle, uint8_t direct, int radius) { // Rotate to given angle, direction, Radius CW = Turn right CCW = Turn left
  leftCount = 0;
  rightCount = 0;
  Serial.println(rot_angle);
  attachInterrupt(digitalPinToInterrupt(RM_ENCODER_A), leftEncoderEvent, RISING);
  attachInterrupt(digitalPinToInterrupt(LM_ENCODER_A), rightEncoderEvent, RISING);

  enc.calculateEncoderIncrements(radius, rot_angle);  //radious(in mm) and angle(in degrees)
  int lowerIncrement = abs(enc.getLowerIncrement());
  int higherIncrement = enc.getHigherIncrement();
  int leftCurrent = leftCount;
  int rightCurrent = rightCount;



  if (direct == CW) {                                 // Turn right
    while (1) {
      if ( higherIncrement > leftCount) {
        motorGo(MOTOR_2, CW, 150);
      }
      else {
//        motorGo(MOTOR_2, CCW, 255);
//        delay(10);
        motorGo(MOTOR_2, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_2, BRAKE, 0);
      }

      if ( lowerIncrement > rightCount) {
        motorGo(MOTOR_1, CCW, 150);
      }
      else {
//        motorGo(MOTOR_1, CW, 255);
//        delay(10);
        motorGo(MOTOR_1, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_1, BRAKE, 0);
      }

      if (( higherIncrement < leftCount) && ( lowerIncrement < rightCount)) {
//        motorGo(MOTOR_1, CW, 255);
//        motorGo(MOTOR_2, CCW, 255);
//        delay(10);
        motorGo(MOTOR_1, BRAKE, 255);
        motorGo(MOTOR_2, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_1, BRAKE, 0);
        motorGo(MOTOR_2, BRAKE, 0);
        delay(20);
        break;
      }
    }
  }

  else if (direct == CCW) {                         // Turn right
    while (1) {
      if ( lowerIncrement > leftCount) {
        motorGo(MOTOR_2, CCW, 150);
      }
      else {
        motorGo(MOTOR_2, CW, 255);
        delay(10);
        motorGo(MOTOR_2, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_2, BRAKE, 0);
      }

      if ( higherIncrement > rightCount) {
        motorGo(MOTOR_1, CW, 150);
      }
      else {
        motorGo(MOTOR_1, CCW, 255);
        delay(20);
        motorGo(MOTOR_1, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_1, BRAKE, 0);
      }

      if ((lowerIncrement < leftCount) && ( higherIncrement < rightCount)) {
        motorGo(MOTOR_1, CCW, 255);
        motorGo(MOTOR_2, CW, 255);
        delay(10);
        motorGo(MOTOR_1, BRAKE, 255);
        motorGo(MOTOR_2, BRAKE, 255);
        delay(20);
        motorGo(MOTOR_1, BRAKE, 0);
        motorGo(MOTOR_2, BRAKE, 0);
        delay(20);
        break;
      }
    }
  }
  detachInterrupt(digitalPinToInterrupt(RM_ENCODER_A));
  detachInterrupt(digitalPinToInterrupt(LM_ENCODER_A));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
