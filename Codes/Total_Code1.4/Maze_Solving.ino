
/////////////////////////////////////////// Sonar get distance//////////////////////////////////////////////////////////////


float getdist(int snr, long tmout = 6000) {

  int trig;
  int echo;
  float duration, d;
  if (snr == 1)
  {
    trig = LF_TRIG;
    echo = LF_ECHO;
  }
  else if (snr == 2)
  {
    trig = LB_TRIG;
    echo = LB_ECHO;
  }
  else if (snr == 3)
  {
    trig = RF_TRIG;
    echo = RF_ECHO;
  }
  else if (snr == 4)
  {
    trig = RB_TRIG;
    echo = RB_ECHO;
  }
  else
  {
    trig = FRNT_TRIG;
    echo = FRNT_ECHO;
  }
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH, tmout);
  d = (duration / 58);
  if (d == 0)
  {
    d = tmout / 58;
  }
  if (d == 51.0) {
    digitalWrite(trig, HIGH);
    delayMicroseconds(8);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH, tmout);
    d = (duration / 58);
    if (d == 0)
    {
      d = tmout / 58;
    }
  }
  return d;

}

////////////////////////////////////////////////
void align()
{
  //  digitalWrite(4,HIGH);
  //  delay(1000);
  //  digitalWrite(4,LOW);

  float distalignf;
  float distalignb;
  float distwfa;
  float distwba;
  float alignerror;
  distwfa = getdist(RF);
  distwba = getdist(RB);
  angle = atan2(abs(distwfa - distwba), 13);
  distalignf = distwfa * abs(cos(angle));
  distalignb = distwba * abs(cos(angle));
  alignerror = distalignf - distalignb;
  Serial.println("");
  Serial.print(distalignf);
  Serial.print(distalignb);
  // if(abs(alignerror)>1)
  // {
  //  digitalWrite(4,HIGH);
  //  delay(2000);
  //  digitalWrite(4,LOW);
  // }

  while (1)
  {
    Serial.println("");
    Serial.print(distalignf);
    Serial.print(distalignb);
    if (alignerror > 0.5)
    {
      //rotateTo(5,CW,0);
      motorGo(MOTOR_2, CW, 80);
      motorGo(MOTOR_1, CCW, 100);
      ;

    }
    else if (alignerror < (-0.5))
    {
      // rotateTo(5,CCW,0);
      motorGo(MOTOR_2, CCW, 80);
      motorGo(MOTOR_1, CW, 100);

    }
    else {
      break;
    }
    delay(50);
    motorGo(MOTOR_2, BRAKE, 0);
    motorGo(MOTOR_1, BRAKE, 0);
    distwfa = getdist(RF);
    distwba = getdist(RB);
    angle = atan2(abs(distwfa - distwba), 13);
    distalignf = distwfa * abs(cos(angle));
    distalignb = distwba * abs(cos(angle));
    alignerror = distalignf - distalignb;
  }
}

////////////////////////////////////////////// Wall Following Function ///////////////////////////////////////////////////////
void wall() {
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  float distwf;
  float distwb;
  float distff;
  float pid = 0;
  float wf_de = 0;
  float wb_de = 0;
  //float wf;
  //float wb;
  //float angle;

  int vl;
  int vr;
  sensor();
  distwf = getdist(RF);
  distwb = getdist(RB);
  distff = getdist(5);
  //turning at edge

  if (distwf > 15)
  { //Serial.print("test");
    // Serial.println(angle * 180 / PI);
    //Serial.println(wb);
    //Serial.println(wf);
    motorGo(MOTOR_2, CCW, 255);
    motorGo(MOTOR_1, CCW, 255);
    delay(20);
    //    motorGo(MOTOR_2, CW, 255);
    //    motorGo(MOTOR_1, CW, 255);
    //    delay(20);
    motorGo(MOTOR_1, BRAKE, 255);
    motorGo(MOTOR_2, BRAKE, 255);
    delay(20);
    motorGo(MOTOR_1, BRAKE, 0);
    motorGo(MOTOR_2, BRAKE, 0);
    //    delay(2000);
    //    while(getdist(RF)>6)
    //    {
    //        motorGo(MOTOR_1, CCW, 150);
    //    motorGo(MOTOR_2, CCW, 170);
    //    }
    //
    //     motorGo(MOTOR_1, BRAKE, 255);
    //    motorGo(MOTOR_2, BRAKE, 255);
    //    delay(20);
    //    motorGo(MOTOR_1, BRAKE, 0);
    //    motorGo(MOTOR_2, BRAKE, 0);
    //    delay(20);
    //    delay(2000);
    //    align();
    //    delay(2000);
    if (edge == false)
    {
      // delay(2000);
      //    while(getdist(RF)>6)
      //    {
      //        motorGo(MOTOR_1, CCW, 150);
      //    motorGo(MOTOR_2, CCW, 170);
      //    }

      //     motorGo(MOTOR_1, BRAKE, 255);
      //    motorGo(MOTOR_2, BRAKE, 255);
      //    delay(20);
      //    motorGo(MOTOR_1, BRAKE, 0);
      //    motorGo(MOTOR_2, BRAKE, 0);
      //    delay(20);
      delay(500);
      goStraightBack(120);
      delay(500);
      align();
      delay(500);
      angle = angle;
      if (getdist(5) < 40)
      {
        goStraight(220);
        while (getdist(5) < 6)
        {
          goStraightBack(20);
        }
        while (getdist(5) > 9)
        {
          goStraight(20);
        }
      }
      else
      {
        goStraight(270);
      }
      delay(500);
      int angg;
      if (wf > wb)
      {
        angg = (int)(90 + round(angle * 180 / PI));
        angg = 90;
        Serial.print(angg);
        rotateTo(angg, CW, 0);
        //rotateTo(90, CW, 0);
      }
      else if (wb > wf)
      {
        angg = (int)(90 - round(angle * 180 / PI));
        angg = 90;
        Serial.print(angg);
        rotateTo(angg, CW, 0);
        //rotateTo(90, CW, 0);
      }
      else
      {
        Serial.print(90);
        rotateTo(90, CW, 0);
      }
    }
    else
    {
      Serial.print(90);
      rotateTo(90, CW, 0);
    }
    //delay(100);
    if ( getdist(5) < 8)
    {
      while(getdist(5)>6)
      {
        goStraight(10);
      }
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      delay(100);
      digitalWrite(GREEN_LED, LOW);
      delay(200);
      digitalWrite(GREEN_LED, HIGH);
      delay(100);
      digitalWrite(GREEN_LED, LOW);
      delay(200);

      armGrab(225, 150, 40);
      finished = true;
    }
    delay(500);
    if (edge == false)
    {
      goStraight(340);
    }
    else
    {
      goStraight(310);
    }

    if (getdist(RF) < 10)
    { delay(500);
      align();
      delay(500);
    }
    wf_last_error = 0;
    edge = true;
    return;
  }
  edge = false;
  if (distff < 13)
  {


    int angg;
    angle = angle;
    Serial.print("testx");
    //    1``as
    motorGo(MOTOR_1, BRAKE, 255);
    motorGo(MOTOR_2, BRAKE, 255);
    delay(20);
    motorGo(MOTOR_1, BRAKE, 0);
    motorGo(MOTOR_2, BRAKE, 0);
    delay(500);
    align();
    delay(500);
    while (getdist(5) < 5)
    {
      goStraightBack(20);
    }
    while (getdist(5) > 12)
    {
      goStraight(20);
    }
    if (wf > wb)
    {
      angg = (int)(90 - round(angle * 180 / PI));
      Serial.print(angg);
      angg = 90;
      rotateTo(angg, CCW, 0);
      //rotateTo(90, CCW, 0);
    }
    else if (wb > wf)
    {
      angg = (int)(90 + round(angle * 180 / PI));
      angg = 90;
      Serial.print(angg);
      rotateTo(angg, CCW, 0);
      //rotateTo(90, CCW, 0);
    }
    else
    {
      Serial.print(90);
      rotateTo(90, CCW, 0);
    }

    delay(500);
    align();
    delay(500);
    if (getdist(RF) > 15 or getdist(RB) > 15)
    {
      delay(1000);
      rotateTo(90, CW, 0);
      while(getdist(5)>6)
      {
        goStraight(20);
      }
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      delay(100);
      digitalWrite(GREEN_LED, LOW);
      delay(200);
      digitalWrite(GREEN_LED, HIGH);
      delay(100);
      digitalWrite(GREEN_LED, LOW);
      delay(200);

      armGrab(225, 150, 40);
      finished = true;
    }
    wf_last_error = 0;
    return;
  }


  angle = atan2(abs(distwf - distwb), 13);
  wf = distwf * abs(cos(angle));
  wb = distwb * abs(cos(angle));

  wf_error = wf - wf_max;

  wf_de = wf_error - wf_last_error;
  wf_last_error = wf_error;
  //pid=wkp*(wf_error+wb_error)+wkd*(wf_de+wb_de);
  pid = wkp * (wf_error) + wkd * (wf_de);
  pid = constrain(pid, -300, 300);
  pre_pid = pid;
  vl = map(pid, -300, 300, -80, 80);
  vr = map(-pid, -300, 300, -80, 80);
  pre_pid = pid;
  //  vl = 100 + vl;
  //  vr = 100 + vr;
  if (pid > 0)
  {
    vl = 180 + vl;
    vr = 200 + vr;
  }
  else
  {
    vl = 180 + vl;
    vr = 220 + vr;
  }
  vl = constrain(vl, -255, 255);
  vr = constrain(vr, -255, 255);
  if (vl > 0) {
    motorGo(MOTOR_2, CW, vl);
  }
  else
  {
    motorGo(MOTOR_2, CCW, abs(vl));
  }
  if (vr > 0)
  {
    motorGo(MOTOR_1, CW, vr);
  }
  else
  {
    motorGo(MOTOR_1, CCW, abs(vr));
  }

  String disp = "";
  disp = disp + "pid:" + pid + " vl:" + vl + " vr:" + vr + " wfe:" + wf_error + " wfde:" + wf_de + " wf:" + distwf + " wb:" + distwb + " angle:" + (angle * 180 / PI);
  Serial.println(disp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

