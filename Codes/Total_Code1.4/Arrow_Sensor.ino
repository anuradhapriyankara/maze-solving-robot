void initSensorPanels() {                       //initialize sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(frontSensorPins[i], INPUT);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(backSensorPins[i], INPUT);
  }
}

void sensor() {                                 //read analog values
  for (int i = 0; i < 5; i++) {
    fSenPanel[i] = analogRead(frontSensorPins[i]);
  }
  for (int i = 0; i < 5; i++) {
    bSenPanel[i] = analogRead(backSensorPins[i]);
  }
}

void scan() {
  sensor();
  if (colour == RED) {
    for (int i = 0; i < 5; i++) {
      fSenPanel[i] = fSenPanel[i] < f_thr_r[i] ? 1 : 0;
      bSenPanel[i] = bSenPanel[i] < b_thr_r[i] ? 1 : 0;
    }
  } else if (colour == GREEN) {
    for (int i = 0; i < 5; i++) {
      fSenPanel[i] = fSenPanel[i] < f_thr_g[i] ? 1 : 0;
      bSenPanel[i] = bSenPanel[i] < b_thr_g[i] ? 1 : 0;
    }
  } else if (colour == BLUE) {
    for (int i = 0; i < 5; i++) {
      fSenPanel[i] = fSenPanel[i] < f_thr_b[i] ? 1 : 0;
      bSenPanel[i] = bSenPanel[i] < b_thr_b[i] ? 1 : 0;
    }
  }

}

void calibrate(int panel) {
  for (int j = 0; j < 5; j++) {
    fSenPanelSum[j] = 0;
  }
  if (panel == FPANEL) {
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);

    Serial.println("Front panel");

    //flushBuffer();
    while (1) {
      Serial.println("Waiting for White");
      if (digitalRead(pushButton) == LOW) {
        break;
      }
    }

    digitalWrite(BLUE_LED, HIGH);

    for (int j = 0; j < 5; j++) {
      fSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("White");
      for (int j = 0; j < 5; j++) {
        fSenPanelSum[j] += analogRead(frontSensorPins[j]);
      }
    }

    for (int i = 0; i < 5; i++) {
      maxVals[i] = fSenPanelSum[i] / 1000;
    }

    //flushBuffer();
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);

    while (1) {
      Serial.println("Waiting for Red");
      if (digitalRead(pushButton) == LOW) {
        break;
      }
    }

    digitalWrite(BLUE_LED, HIGH);

    for (int j = 0; j < 5; j++) {
      fSenPanelSum[j] = 0;
    }

    for (int i = 0; i < 1000; i++) {
      Serial.println("Red");
      for (int j = 0; j < 5; j++) {
        fSenPanelSum[j] += analogRead(frontSensorPins[j]);
      }
    }
    for (int i = 0; i < 5; i++) {
      minVals[i] = fSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      f_thr_r[i] = (maxVals[i] + minVals[i]) / 2;
    }

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);

    while (1) {
      Serial.println("Waiting for Green");
      if (digitalRead(pushButton) == LOW) {
        break;
      }
    }

    digitalWrite(BLUE_LED, HIGH);

    for (int j = 0; j < 5; j++) {
      fSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("Green");
      for (int j = 0; j < 5; j++) {
        fSenPanelSum[j] += analogRead(frontSensorPins[j]);
      }
    }

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);

    for (int i = 0; i < 5; i++) {
      minVals[i] = fSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      f_thr_g[i] = (maxVals[i] + minVals[i]) / 2;
    }
    digitalWrite(BLUE_LED, HIGH);
    while (1) {
      Serial.println("Waiting for Blue");
      if (digitalRead(pushButton) == LOW) {
        break;
      }
    }

    for (int j = 0; j < 5; j++) {
      fSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("Blue");
      for (int j = 0; j < 5; j++) {
        fSenPanelSum[j] += analogRead(frontSensorPins[j]);
      }
    }
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
    for (int i = 0; i < 5; i++) {
      minVals[i] = fSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      f_thr_b[i] = (maxVals[i] + minVals[i]) / 2;
    }

  } else if (panel == BPANEL) {
    Serial.println("Back panel");

    flushBuffer();
    while (!Serial.available()) {
      Serial.println("Waiting for White");
    }
    for (int j = 0; j < 5; j++) {
      bSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("White");
      for (int j = 0; j < 5; j++) {
        bSenPanelSum[j] += analogRead(backSensorPins[j]);
      }
    }
    for (int i = 0; i < 5; i++) {
      maxVals[i] = bSenPanelSum[i] / 1000;
    }

    flushBuffer();
    while (!Serial.available()) {
      Serial.println("Waiting for Red");
    }
    for (int j = 0; j < 5; j++) {
      bSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("Red");
      for (int j = 0; j < 5; j++) {
        bSenPanelSum[j] += analogRead(backSensorPins[j]);
      }
    }
    for (int i = 0; i < 5; i++) {
      minVals[i] = bSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      b_thr_r[i] = (maxVals[i] + minVals[i]) / 2;
    }

    flushBuffer();
    while (!Serial.available()) {
      Serial.println("Waiting for Green");
    }
    for (int j = 0; j < 5; j++) {
      bSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("Green");
      for (int j = 0; j < 5; j++) {
        bSenPanelSum[j] += analogRead(backSensorPins[j]);
      }
    }
    for (int i = 0; i < 5; i++) {
      minVals[i] = bSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      b_thr_g[i] = (maxVals[i] + minVals[i]) / 2;
    }

    flushBuffer();
    while (!Serial.available()) {
      Serial.println("Waiting for Blue");
    }
    for (int j = 0; j < 5; j++) {
      bSenPanelSum[j] = 0;
    }
    for (int i = 0; i < 1000; i++) {
      Serial.println("Blue");
      for (int j = 0; j < 5; j++) {
        bSenPanelSum[j] += analogRead(backSensorPins[j]);
      }
    }
    for (int i = 0; i < 5; i++) {
      minVals[i] = bSenPanelSum[i] / 1000;
    }

    for (int i = 0; i < 5; i++) {
      b_thr_b[i] = (maxVals[i] + minVals[i]) / 2;
    }
  }
  Serial.println("Done");
  //  for(int j=0; j<5; j++){
  //    Serial.print(maxVals[j]);
  //    Serial.print(" || ");
  //  }
  //  for(int j=0; j<5; j++){
  //    Serial.print(minVals[j]);
  //    Serial.print(" || ");
  //  }
}

void printThr() {
  Serial.println("Front Thr : ");
  Serial.print("Red : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(f_thr_r[i]);
    Serial.print(" || ");
  }
  Serial.println();

  Serial.print("Green : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(f_thr_g[i]);
    Serial.print(" || ");
  }
  Serial.println();

  Serial.print("Blue : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(f_thr_b[i]);
    Serial.print(" || ");
  }
  Serial.println();


  Serial.println("Back Thr : ");
  Serial.print("Red : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(b_thr_r[i]);
    Serial.print(" || ");
  }
  Serial.println();

  Serial.println("Back Thr : ");
  Serial.print("Green : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(b_thr_g[i]);
    Serial.print(" || ");
  }
  Serial.println();

  Serial.println("Back Thr : ");
  Serial.print("Blue : ");
  for (int i = 0; i < 5; i++) {
    Serial.print(b_thr_b[i]);
    Serial.print(" || ");
  }
  Serial.println();
}

void flushBuffer() {
  while (Serial.available()) {
    Serial.read();
  }
}

