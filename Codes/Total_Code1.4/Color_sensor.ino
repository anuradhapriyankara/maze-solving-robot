

////////////////////////// Color Sensor Codes ////////////////////////////////////////////

int colorout() {
  sensorread();
  if (Rval > wval && Gval > wval && Bval > wval && (Rval < 500 && Gval < 500 && Bval < 500)) {
    if (min (Rval, Gval) == Rval && min (Rval, Bval) == Rval &&  ((Rval <= redTH[0] + diff) || (Rval >= redTH[0] - diff))) {
      Serial.println("Red");
      return RED;
    }

    else if ( min (Rval, Gval) == Gval && min (Gval, Bval) == Gval && ((Gval <= greenTH[1]+diff) || (Gval>= greenTH[1]-diff)) && (Bval > blueTH[2]+diff)) {
      Serial.println("Green");
      return GREEN;
    }
    else if (min (Rval, Bval) == Bval && min (Gval, Bval) == Bval && (Rval >  redTH[0]+diff) && (Gval > greenTH[1]+diff) && ((Bval <= blueTH[2]+diff) || (Bval>= blueTH[2]-diff))) {
      Serial.println("Blue");
      return BLUE;
    }
    else {
      return 0;
    }
  }
}

int coloroutbox() {
  sensorreadbox();
  if (Rval > wval && Gval > wval && Bval > wval && (Rval < 400 && Gval < 400 && Bval < 400)) {
    if (min (Rval, Gval) == Rval && min (Rval, Bval) == Rval &&  ((Rval <= redTH[0] + diff) || (Rval >= redTH[0] - diff))) {
      Serial.println("Red");
      return RED;
    }

        else if ( min (Rval, Gval) == Gval && min (Gval, Bval) == Gval && ((Gval <= greenTH[1]+diff) || (Gval>= greenTH[1]-diff)) && (Bval > blueTH[2]+diff)) {
          Serial.println("Green");
          return GREEN;
        }
        else if (min (Rval, Bval) == Bval && min (Gval, Bval) == Bval && (Rval >  redTH[0]+diff) && (Gval > greenTH[1]+diff) && ((Bval <= blueTH[2]+diff) || (Bval>= blueTH[2]-diff))) {
          Serial.println("Blue");
          return BLUE;
        }
    else {
      return 0;
    }
  }
}
void sensorread() {

  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  Rval = frequency;
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Gval = frequency;
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  Bval = frequency;
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  //delay(100);

}

void sensorreadbox() {

  // Setting red filtered photodiodes to be read
  digitalWrite(S2box, LOW);
  digitalWrite(S3box, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOutbox, LOW);
  Rval = frequency;
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2box, HIGH);
  digitalWrite(S3box, HIGH);
  frequency = pulseIn(sensorOutbox, LOW);
  Gval = frequency;
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  //delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2box, LOW);
  digitalWrite(S3box, HIGH);
  frequency = pulseIn(sensorOutbox, LOW);
  Bval = frequency;
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  //delay(100);

}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void calibrateColor() {
  buzz_r(600);    // Calibrating for the white background
  sensorread();
//  while ( Rval > 120 || Bval > 120 || Gval > 120) {
//    Serial.println("waiting for white ");
//    sensorread();
//  }
  while(1){                   // waiting for white
    digitalWrite(BLUE_LED,HIGH);
    delay(100);
    digitalWrite(BLUE_LED,LOW);
    delay(200);
    Serial.println("---- waiting for white ---- ");
    if(digitalRead(pushButton)==LOW){
      digitalWrite(BLUE_LED,LOW);
      break;
    }
  }
  buzz_r(100);
  int w=0;
  for ( int i = 0; i <= 20 ; i++) {
    sensorread();
    wval+=(Rval+Gval+Bval)/3;
    Serial.println("--------------white calibrating-------------- ");
  }
  wval = wval / 20;
  Serial.print("wval: ");
  Serial.print(wval);
  buzz_r(500);
  delay(1000);

  //----------------------------------------------
  //Calibration for the red threshold
  sensorread();
  while(1){                   // waiting for white
    digitalWrite(BLUE_LED,HIGH);
    delay(100);
    digitalWrite(BLUE_LED,LOW);
    delay(200);
    Serial.println("---- waiting for red ---- ");
    if(digitalRead(pushButton)==LOW){
      digitalWrite(BLUE_LED,LOW);
      break;
    }
  }
  buzz_r(100);
  for (int j = 0; j <= 20; j++) {
    sensorread();
    Serial.println("red calibrating_ ");
    Serial.print(Rval);
    RTh += Rval;
  }
  RTh = RTh / 20;
  Serial.print("                  Rthreshold: ");
  Serial.print(RTh);
  buzz_r(500);
  delay(1000);
  //-----------------------------------------------------
  // calibration of green
//  while(Rval>250 || Bval<120){
//       Serial.println("Waiting for Green");
//       sensorread();
//  }
  while(1){                   // waiting for white
    digitalWrite(BLUE_LED,HIGH);
    delay(100);
    digitalWrite(BLUE_LED,LOW);
    delay(200);
    Serial.println("---- waiting for green ---- ");
    if(digitalRead(pushButton)==LOW){
      digitalWrite(BLUE_LED,LOW);
      break;
    }
  }
    buzz_r(100);
    for (int k = 0; k <= 20; k++) {
      sensorread();
      Serial.println("green calibrating_ ");
      Serial.print(Gval);
      GTh += Gval;
    }
    GTh = GTh / 20;
    Serial.println("            Gthreshold: ");
    Serial.print(GTh);
  buzz_r(500);
  delay(1000);

  //-------------------------------------------------------
  //Calibration for the Blue threshold
  while(1){                   // waiting for white
    digitalWrite(BLUE_LED,HIGH);
    delay(100);
    digitalWrite(BLUE_LED,LOW);
    delay(200);
    Serial.println("---- waiting for blue ---- ");
    if(digitalRead(pushButton)==LOW){
      digitalWrite(BLUE_LED,LOW);
      break;
    }
  }
    buzz_r(100);
    for (int l = 0; l <= 20; l++) {
      sensorread();
      Serial.println("blue calibrating_ ");
      Serial.print(Bval);
      BTh += Bval;
    }
    BTh = BTh / 20;
    Serial.print("               Bthreshold: ");
    Serial.print(BTh);
    buzz_r(500);
  delay(500);
  buzz_r(500);
  delay(500);
  buzz_r(500);
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void buzz_r(int dur) {
  digitalWrite(buzzer, HIGH);
  delay(dur);
  digitalWrite(buzzer, LOW);
  delay(100);
}
