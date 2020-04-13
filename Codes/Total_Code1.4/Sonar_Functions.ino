//
//
///////////////////////////////////////////// Sonar get distance//////////////////////////////////////////////////////////////
//float getdist(int snr, long tmout = 3000){
//
//  int trig;
//  int echo;
//  float duration, d;
//  if (snr == 1)
//  {
//    trig = LF_TRIG;
//    echo = LF_ECHO;
//  }
//  else if (snr == 2)
//  {
//    trig = LB_TRIG;
//    echo = LB_ECHO;
//  }
//  else if (snr == 3)
//  {
//    trig = RF_TRIG;
//    echo = RF_ECHO;
//  }
//  else if (snr == 4)
//  {
//    trig = RB_TRIG;
//    echo = RB_ECHO;
//  }
//  else
//  {
//    trig = FRNT_TRIG;
//    echo = FRNT_ECHO;
//  }
//  digitalWrite(trig, HIGH);
//  delayMicroseconds(8);
//  digitalWrite(trig, LOW);
//  duration = pulseIn(echo, HIGH, tmout);
//  d = (duration / 58);
//  if (d == 0)
//  {
//    d = tmout / 58;
//  }
//  if (d == 51.0) {
//    digitalWrite(trig, HIGH);
//    delayMicroseconds(8);
//    digitalWrite(trig, LOW);
//    duration = pulseIn(echo, HIGH, tmout);
//    d = (duration / 58);
//    if (d == 0)
//    {
//      d = tmout / 58;
//    }
//  }
//  return d;
//  
//}
