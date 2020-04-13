/////////// Import Libraries ///////////////////////////////////////////////////////////////////////////
#include <EncoderCal.h>
#include <Servo.h>
#include <EEPROM.h>

////////////////// EEPROM Parameters //////////////////////////////////////////////////////////////////
int eeCurrentAddress = 500;
int eeStartAddress = 500;
struct sensorValues {
  int s1;
  int s2;
  int s3;
  int s4;
  int s5;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////

////////// Servo Motor ////////////////////////////////////////////////////////////////////////////////
Servo myservo;
#define SERVO_PIN 12
///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////// Motor Encoder /////////////////////////////////////////////////////////////////////////////
#define RM_ENCODER_A 3
#define LM_ENCODER_A 2

EncoderCal enc(230, 65, 175);// Encoder Ratio, Wheel Diameter, Wheel Gap  (all distances in mm scale)

//Motor control//////////////////////////////////////////////////////////////////////////////////////////
#define BRAKE 0
#define CW    1 // Forward
#define CCW   2 // Backward
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

#define MOTOR_A1_PIN 39//MOTOR 1
#define MOTOR_B1_PIN 38

#define MOTOR_A2_PIN 40//MOTOR 2
#define MOTOR_B2_PIN 41

#define ARM_MOTOR_A1_PIN 43//Arm Motor
#define ARM_MOTOR_B1_PIN 42

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6
#define PWM_ARM_MOTOR 7

#define EN_PIN_1 A0 // Motor Enable pins
#define EN_PIN_2 A1
#define EN_PIN_3 A2

#define MOTOR_1 1 //RIGHT MOTOR
#define MOTOR_2 0 //LEFT MOTOR

volatile unsigned long leftCount = 0;  // Left encoder count
volatile unsigned long rightCount = 0; // Right encoder count
///////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////// Sonar Pins //////////////////////////////////////////////////////////////////////
#define LF 1
#define LB 2
#define RF 3

#define RB 4
#define FR 5

#define LB_TRIG 52 //Sonar 1 Left - Back Sonar
#define LB_ECHO 53

#define LF_TRIG 46 //Sonar 2 Left - Front Sonar
#define LF_ECHO 47

#define RB_TRIG 50 //Sonar 4 Right - Front Sonat
#define RB_ECHO 51

#define RF_TRIG 48 //Sonar 3 Right -Back Sonar
#define RF_ECHO 49

#define FRNT_TRIG 44 //Sonar 5 Front Sonar
#define FRNT_ECHO 45

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////// Wall Following Parameters //////////////////////////////////////////////////////////////////
int wkp = 20;
int wkd = 150;

float wf_error = 0;
float wf_last_error = 0;
float wf_max = 5;

float wb_error = 0;
float wb_last_error = 0;
float wb_max = 15;
float pre_pid = 0;

float angle;
float wf;
float wb;
bool edge = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////// Arrow Follow Parameters /////////////////////////////////////////

int fSenVal = 0;                                                            //value of the front sensor panel
int bSenVal = 0;                                                            //value of the back sensor panel
int fPanel[5] = {0, 0, 0, 0, 0};                                            //states of the front panel sensors
int bPanel[5] = {0, 0, 0, 0, 0};                                            //states of the back panel sensors
boolean dirDetect = false;                                                  //whether the direction of the arrow is detected
boolean activatePanel = false;                                              //whether the panels should be activated
int fSenValSum = 0;
int lastFVal = 0;
int count = 0;
boolean activePanel;
boolean arrowFound = false;
boolean panelSide  = 0;
int maxPanelValue = 0;
int fSenVal1 = 0;
int fSenVal2 = 0;
int Pwm;
boolean ended = false;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////// Sensor Panel Parameters /////////////////////////////////////////

#define FPANEL 0
#define BPANEL 1
#define RED 1
#define GREEN 2
#define BLUE 3

const int frontSensorPins[5] = {A12, A11, A10, A9, A8};
const int backSensorPins[5] = {A7, A6, A5, A4, A3};

int fSenPanel[5] = {0, 0, 0, 0, 0};
int bSenPanel[5] = {0, 0, 0, 0, 0};

int f_thr_r[5] = {867, 848, 856, 890, 846};
int f_thr_g[5] = {849, 825, 838, 879, 824};
int f_thr_b[5] = {859, 836, 846, 887, 838};
//int f_thr[5] = {0,0,0,0,0};

int b_thr_r[5] = {0, 0, 0, 0, 0};
int b_thr_g[5] = {0, 0, 0, 0, 0};
int b_thr_b[5] = {0, 0, 0, 0, 0};
//int b_thr[5] = {0,0,0,0,0};

long fSenPanelSum[5] = {0, 0, 0, 0, 0};
long bSenPanelSum[5] = {0, 0, 0, 0, 0};
int maxVals[5] = {0, 0, 0, 0, 0};
int minVals[5] = {0, 0, 0, 0, 0};

int colour = RED;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// Go Straight Parameters /////////////////////////////////////////////
float kp = 0.2;
float ki = 0;
float kd = 0.6;
int error = 0;
int lastError = 0;
int errorSum = 0;
int normalPWM = 50;
int addPWM = 0;

////////////////////////////////////////// Color Sensor Parameters ///////////////////////////////////////////

#define S0 32
#define S1 33
#define S2 34
#define S3 35
#define sensorOut 36

#define S0box 26
#define S1box 27
#define S2box 28
#define S3box 29
#define sensorOutbox 12

#define buzzer 4
#define button
#define RED 1
#define GREEN 2
#define BLUE 3

int frequency = 0;
int diff = 10;
int Rval = 0;
int Gval = 0;
int Bval = 0;
int wval = 57;
int RTh = 0, GTh = 0, BTh = 0;
int whiteTH[3] = {0, 0, 0};
int redTH[3] = {98, 220, 149};
int greenTH[3] = {230, 162, 133};
int blueTH[3] = {255, 235, 99};

////////////////////////////////// Global Variable declaration ends here /////////////////////////////////////


/////////////////////////////////////////// Switches  /////////////////////////////////////////////////////////
#define pushButton 10
#define sw_calibrate 24
#define sw_r 22
#define sw_g 25
#define sw_b 23

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// LEDs //////////////////////////////////////////////////////////////
#define BLUE_LED 8
#define GREEN_LED 9
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool finished = false;


void setup() {
  //Encoder interrupts
  //  attachInterrupt(digitalPinToInterrupt(RM_ENCODER_A), leftEncoderEvent, RISING);
  //  attachInterrupt(digitalPinToInterrupt(LM_ENCODER_A), rightEncoderEvent, RISING);

  Serial.begin(9600);
  //Sonar Setup
  pinMode(LF_TRIG, OUTPUT);
  pinMode(LF_ECHO, INPUT);

  pinMode(LB_TRIG, OUTPUT);
  pinMode(LB_ECHO, INPUT);

  pinMode(RF_TRIG, OUTPUT);
  pinMode(RF_ECHO, INPUT);

  pinMode(RB_TRIG, OUTPUT);
  pinMode(RB_ECHO, INPUT);

  pinMode(FRNT_TRIG, OUTPUT);
  pinMode(FRNT_ECHO, INPUT);

  //Motor control
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);
  pinMode(EN_PIN_3, OUTPUT);

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);
  digitalWrite(EN_PIN_3, HIGH);

  // Limit Switches
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);

  // Function Switches
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);

  // Push Button
  pinMode(pushButton, INPUT_PULLUP);

  // LEDs
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  analogWrite(4, 125);
  delay(200);
  analogWrite(4, 180);
  delay(200);
  analogWrite(4, 80);
  delay(200);
  digitalWrite(4, LOW);

  //  if(digitalRead(sw_calibrate)==LOW){
  //    calibrate(FPANEL);
  //    printThr();
  //  }
  //  else if(digitalRead(sw_r)==LOW){
  //    colour=RED;
  //
  //  }
  //  else if(digitalRead(sw_g)==LOW){
  //    colour=GREEN;
  //
  //  }
  //  else if(digitalRead(sw_b)==LOW){
  //    colour=BLUE;
  //
  //  }
  armGrab(225, 150, 40);
  delay(2000);
  armRelease(220, 150, 40);





}

void loop() {


  //  while (1) {
  //    digitalWrite(BLUE_LED, HIGH);
  //    wall();
  //    if (finished) {
  //      break;
  //    }
  //  }
  //
  //  goStraight(200);
  //
  //  if(colour == RED){
  //    //do nothing
  //  }else if(colour == GREEN){
  //    rotateTo(20,CCW, 0);
  //  }else if(colour = BLUE){
  //    rotateTo(20,CW, 0);
  //  }
  //  delay(500);
  //  while(colourDetected()){
  //    goStraight(10);
  //  }
  //
  //
  //  while (1) {
  //    arrowFollow() ;
  //    if (ended) {
  //      break;
  //    }
  //  }
  //  while (1) {
  //    //wall();
  //  }


}
