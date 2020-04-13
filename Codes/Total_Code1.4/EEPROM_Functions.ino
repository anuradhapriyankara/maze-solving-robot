//
//void showVals(){
//  for(int i=0;i<5;i++){
//    //Serial.println(thers_g_frnt[i]);
//  }
//}
//void putToROM(int vals[5]){
//  sensorValues thers_vals={
//    vals[0],
//    vals[1],
//    vals[2],
//    vals[3],
//    vals[4],
//  };
//  
//   EEPROM.put(eeCurrentAddress, thers_vals);
//   eeCurrentAddress+=(sizeof(int)*5);
//}
////struct sensorValues {
////  int s1;
////  int s2;
////  int s3;
////  int s4;
////  int s5;
////};
//
//
//void getFromEEPROM(){
//  for(int i=0;i<7;i++){
//    sensorValues storedVals;
//    if(i==0){
//      EEPROM.get(eeStartAddress, storedVals);
//      eeStartAddress+=(sizeof(int)*5);;
////      thers_r_frnt[0]=storedVals.s1;
////      thers_r_frnt[1]=storedVals.s2;
////      thers_r_frnt[2]=storedVals.s3;
////      thers_r_frnt[3]=storedVals.s4;
////      thers_r_frnt[4]=storedVals.s5;
//    }
//    if(i==1){
//      EEPROM.get(eeStartAddress, storedVals);
//      eeStartAddress+=(sizeof(int)*5);;
////      thers_g_frnt[0]=storedVals.s1;
////      thers_g_frnt[1]=storedVals.s2;
////      thers_g_frnt[2]=storedVals.s3;
////      thers_g_frnt[3]=storedVals.s4;
////      thers_g_frnt[4]=storedVals.s5;
//    }
// }
