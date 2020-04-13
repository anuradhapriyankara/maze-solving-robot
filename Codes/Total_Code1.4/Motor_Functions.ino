//////////////////////// Motor Controlling //////////////////////////////////////////////////////////////////////////////////////
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)//Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if (motor == MOTOR_1) // Motor 1
  {
    if (direct == CW)   // Forward
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if (direct == CCW) // Reverse
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    else                    // Brake
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_1, pwm);
  }
  else if (motor == MOTOR_2) // Motor 2
  {
    if (direct == CCW)       // Reverse
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if (direct == CW)   // Forward
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    else                     // Brake
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_2, pwm);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////// Motor Functions ////////////////////////////////////////////////////////////////////////////
void motorForward(int left_m, int right_m) {
  motorGo(MOTOR_1, CW, right_m);
  motorGo(MOTOR_2, CW, left_m);
}

void motorReverse(int left_m, int right_m) {
  motorGo(MOTOR_1, CCW, right_m);
  motorGo(MOTOR_2, CCW, left_m);
}

void motorTurnLeft() {
  motorGo(MOTOR_1, CW, 150);
  motorGo(MOTOR_2, CCW, 150);
}

void motorTurnRight() {
  motorGo(MOTOR_1, CCW, 150);
  motorGo(MOTOR_2, CW, 150);
}

void rightBrake( int leftPWM){
  motorGo(MOTOR_1, BRAKE, 225);
  motorGo(MOTOR_2, CW, leftPWM);
}

void leftBrake( int rightPWM){
  
  motorGo(MOTOR_2, BRAKE, 225);
  motorGo(MOTOR_1, CW, rightPWM);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


