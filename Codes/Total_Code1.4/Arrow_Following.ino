void arrowFollow() {
  activePanel = true;
  while (activePanel) {
    scan();
    fSenVal1 = 100 * fSenPanel[0] + 200 * fSenPanel[1] - 200 * fSenPanel[3] - 100 * fSenPanel[4];
    fSenVal2 = 100 * fSenPanel[0] + 200 * fSenPanel[1] + 200 * fSenPanel[3] + 100 * fSenPanel[4];
    if(fSenVal1 == 0){
      motorForward(80,80);
    }else{
      
      if(fSenVal2 == 0){
        break;
      }else{
        Pwm = (400 - fSenVal2)/10; 
        if(fSenVal1 > 0){
          motorForward(100 - Pwm,80 + Pwm);
        }else{
          motorForward(100 + Pwm,80 - Pwm);
        }
      }
      
    }

    if(fSenVal2 >= 500 && colourDetected){
      motorReverse(100,100);
      delay(1000);
      armRelease(220,150,40);
      ended = true;
      break;
    }
  }

    
}
void refreshSenVals() {
  fSenValSum = 0;
  lastFVal = 0;
  count = 0;
  maxPanelValue = 0;
}

boolean colourDetected() {
  if (colorout() == colour) {
    return true;     //color sensor code should be here
  }
  else {
    return false;
  }
}

void getFSenVal() {
  scan();
  fSenVal = 100 * fSenPanel[0] + 200 * fSenPanel[1] + 400 * fSenPanel[2] + 800 * fSenPanel[3] + 1600 * fSenPanel[4];
  maxPanelValue = fSenVal > maxPanelValue ? fSenVal : maxPanelValue;
}
