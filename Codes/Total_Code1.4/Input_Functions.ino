void waitForInput(){
  while(1){
    digitalWrite(BLUE_LED,HIGH);
    delay(100);
    digitalWrite(BLUE_LED,LOW);
    delay(200);
    if(digitalRead(pushButton)==LOW){
      digitalWrite(BLUE_LED,LOW);
      break;
    }
  }
}

