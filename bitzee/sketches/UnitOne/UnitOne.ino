/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/*
   UnitOne
   Basic tests
   
   Pin outs
   A5-Rear bumper switch by speaker
   A4-Front bumper switch by IR receiver
   A1-Green LEDs
   A0-Red LEDs
   A2-Blue LEDs

   D9-Motor L3
   D3-sound play
   D7-Motor L4
   D2-sound rec
   D5-Camera enbable
   D6–Motor E1-2 /E3-4 Yellow on Manuel
   D9-Open- unused green wire
   D8-Motor L2
   D10-Motor L1
   D11-front IR sensor
   D12-rear IR sensor
   D4-Camera shutter
*/

#include <IRremote.h>


const int REMOTE_1_1     = 0x597B;
const int REMOTE_1_2     = 0x10CE;
const int REMOTE_2_1     = 0x797E;
const int REMOTE_2_2     = 0x20CD;
const int REMOTE_3_1     = 0x1DBF;
const int REMOTE_3_2     = 0x30CC;
const int REMOTE_4_1     = 0x40CB;
const int REMOTE_4_2     = 0x53D6;
const int REMOTE_5_1     = 0x50CA;
const int REMOTE_5_2     = 0x4EDF;
const int REMOTE_6_1     = 0xDA9A;
const int REMOTE_6_2     = 0x60C9;
const int REMOTE_7_1     = 0x70C8;
const int REMOTE_7_2     = 0x70DB;
const int REMOTE_8_1     = 0x0E7E;
const int REMOTE_8_2     = 0x80C7;
const int REMOTE_9_1     = 0x1877;
const int REMOTE_9_2     = 0x90C6;
const int REMOTE_DOT_1   = 0xAF5F;
const int REMOTE_DOT_2   = 0x7018;
const int REMOTE_0_1     = 0xDF7A;
const int REMOTE_0_2     = 0x00CF;
const int REMOTE_ENTER_1 = 0x400B;
const int REMOTE_ENTER_2 = 0xB4FE;
const int REMOTE_REW_1   = 0x79C3;
const int REMOTE_REW_2   = 0xD1E2;
const int REMOTE_PLAY_1  = 0xB57F;
const int REMOTE_PLAY_2  = 0x51EA;
const int REMOTE_FF_1    = 0x0FBA;
const int REMOTE_FF_2    = 0xC1E3;
const int REMOTE_REC_1   = 0x2EC3;
const int REMOTE_REC_2   = 0x71E8;
const int REMOTE_STOP_1  = 0x3ABF;
const int REMOTE_STOP_2  = 0xF1E0;
const int REMOTE_PAUSE_1 = 0xCB5F;
const int REMOTE_PAUSE_2 = 0x91E6;
const int REMOTE_PWR_1   = 0xB3C4;
const int REMOTE_PWR_2   = 0xA0D5;

const int PIN_BMP_R = A5;
const int PIN_BMP_F = A4;
const int PIN_LED_G = A1;
const int PIN_LED_R = A0;
const int PIN_LED_B = A2;

const int PIN_CAM_IMG = 4;
const int PIN_AUD_R   = 2;
const int PIN_AUD_P   = 3;
const int PIN_CAM_PWR = 5;
const int PIN_RIR_RCV = 12;
const int PIN_FIR_RCV = 11;

const int PIN_MTR_EN  = 6;
const int PIN_MTR_L1  = 10;
const int PIN_MTR_L2  = 8;
const int PIN_MTR_L3  = 9;
const int PIN_MTR_L4  = 7;

const int FULL = 255;
const int SLOW = 150;



IRrecv irrecv(PIN_RIR_RCV);
decode_results results;


// the setup routine runs once when you press reset:
void setup() {
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  pinMode(PIN_BMP_R, INPUT);
  pinMode(PIN_BMP_F, INPUT);

  pinMode(PIN_AUD_R, OUTPUT);
  pinMode(PIN_AUD_P, OUTPUT);

  pinMode(PIN_CAM_PWR, OUTPUT);
  pinMode(PIN_CAM_IMG, OUTPUT);
  
  pinMode(PIN_MTR_EN, OUTPUT);
  pinMode(PIN_MTR_L1, OUTPUT);
  pinMode(PIN_MTR_L2, OUTPUT);
  pinMode(PIN_MTR_L3, OUTPUT);
  pinMode(PIN_MTR_L4, OUTPUT);

  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    int code = results.value & 0xFFFF;
    //Serial.println(code, HEX);
    dispatchCommand(code);
    irrecv.resume(); // Receive the next value
  }
  if (fwdBump()) {
    playSound();
    lightsFlash();
  }
  if (bwdBump()) {
    playSound();
    lightsFlash();
  }  
}

int lastButton = 0;

void dispatchCommand(int code) {
  switch (code) {
      case REMOTE_1_1:
      case REMOTE_1_2:
        Serial.println("1");
        waddle();
        break;
      case REMOTE_2_1:
      case REMOTE_2_2:
        Serial.println("2");
        wiggle();
        break;
      case REMOTE_3_1:
      case REMOTE_3_2:
        Serial.println("3");
        powerSlideRight();
        break;
      case REMOTE_4_1:
      case REMOTE_4_2:
        Serial.println("4");
        spinRight(3000);
        break;
      case REMOTE_5_1:
      case REMOTE_5_2:
        Serial.println("5");
        spinLeft(3000);
        break;
      case REMOTE_6_1:
      case REMOTE_6_2:
        Serial.println("6");
        powerSlideLeft();
        break;
      case REMOTE_7_1:
      case REMOTE_7_2:
        Serial.println("7");
        rightFwd();
        break;
      case REMOTE_8_1:
      case REMOTE_8_2:
        Serial.println("8");
        figureEight();
        break;
      case REMOTE_9_1:
      case REMOTE_9_2:
        Serial.println("9");
        waddleBwd();
        break;
      case REMOTE_DOT_1:
      case REMOTE_DOT_2:
        Serial.println("DOT");
        lastButton = REMOTE_DOT_1;
        break;
      case REMOTE_0_1:
      case REMOTE_0_2:
        Serial.println("0");
        break;
      case REMOTE_ENTER_1:
      case REMOTE_ENTER_2:
        Serial.println("ENTER");
        if (lastButton == REMOTE_DOT_1) {
            recordSound();
        }
        break;
      case REMOTE_PLAY_1:
      case REMOTE_PLAY_2:
        Serial.println("PLAY");
        playSound();
        break;
      case REMOTE_REW_1:
      case REMOTE_REW_2:
        Serial.println("REW");
        //bwdSpeed(SLOW);
        //bwd(0);
        bwdFaster();
        break;
      case REMOTE_FF_1:
      case REMOTE_FF_2:
        Serial.println("FF");
        //fwdSpeed(SLOW);
        //fwd(0);
        fwdFaster();
        break;
      case REMOTE_REC_1:
      case REMOTE_REC_2:
        Serial.println("REC");
        recordImage();
        break;
      case REMOTE_STOP_1:
      case REMOTE_STOP_2:
        Serial.println("STOP");
        stopSound();
        powerStop();
        break;
      case REMOTE_PAUSE_1:
      case REMOTE_PAUSE_2:
        Serial.println("PAUSE");
        rightStop();
        leftStop();
        break;
      case REMOTE_PWR_1:
      case REMOTE_PWR_2:
        Serial.println("ON/OFF");
        lightsFlash();
        break;
      default:
        break;
  }
}

// BEHAVIORS

void lightsFlash() {
  lightsOn(100, 1, 0, 0);
  lightsOn(100, 0, 1, 0);
  lightsOn(100, 0, 0, 1);
  
  lightsOn(300, 1, 0, 1);
  lightsOn(300, 1, 1, 0);
  lightsOn(300, 0, 1, 1);
  
  lightsOn(100, 1, 0, 0);
  lightsOn(100, 0, 1, 0);
  lightsOn(100, 0, 0, 1);
  
  lightsOn(100, 1, 0, 1);
  lightsOn(100, 1, 1, 0);
  lightsOn(100, 0, 1, 1);
  
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
}

void powerSlideLeft() {
  fwdSpeed(FULL);
  fwd(2000);
  spinLeft(500);
  bwd(300);
}

void powerSlideRight() {
  fwdSpeed(FULL);
  fwd(2000);
  spinLeft(500);
  bwd(300);
}


void figureEight() {
  leftFwd();
  rightFwd();
  //delay(1000);
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
  leftStop();
  //delay(1000);
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
  leftFwd();
  //delay(1000);
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
  rightStop();
  //delay(1000);
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
  rightFwd();
  //delay(1000);
  lightsOn(300, 1, 0, 0);
  lightsOn(300, 0, 1, 0);
  lightsOn(300, 0, 0, 1);
  leftStop();
  rightStop();
}

void wiggle() {
  fwdSpeed(random(FULL-20, FULL));  
  bwdSpeed(random(FULL-20, FULL));  
  for (int i=0; i < 10; i++) {
    spinLeft(random(150,220)); 
    delay(random(150,220)); 
    spinRight(random(150,220));
    delay(random(150,220));
  }
  stop();
  lightsFlash();
}

void waddle() {
  fwdSpeed(FULL);
  for (int i=0; i < 5; i++) {
    waddleLeft();
    //delay(1000);
    lightsOn(300, 1, 0, 0);
    lightsOn(300, 0, 1, 0);
    lightsOn(300, 0, 0, 1);
    waddleRight();
    //delay(1000);
    lightsOn(300, 1, 0, 0);
    lightsOn(300, 0, 1, 0);
    lightsOn(300, 0, 0, 1);
  }
}

void waddleLeft() {
  rightStop();
  leftFwd();
  //delay(300);
  lightsOn(300, 1, 0, 0);
  leftStop();
  rightFwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  rightStop();
  leftFwd();
  //delay(300);
  lightsOn(300, 0, 0, 1);
  leftStop();
  rightFwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  rightStop();
}

void waddleRight() {
  leftStop();
  rightFwd();
  //delay(300);
  lightsOn(300, 1, 0, 0);
  rightStop();
  leftFwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  leftStop();
  rightFwd();
  //delay(300);
  lightsOn(300, 0, 0, 1);
  rightStop();
  leftFwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  leftStop();
}

void waddleBwd() {
  fwdSpeed(FULL);
  for (int i=0; i < 5; i++) {
    waddleLeft();
    //delay(1000);
    lightsOn(300, 1, 0, 0);
    lightsOn(300, 0, 1, 0);
    lightsOn(300, 0, 0, 1);
    waddleRight();
    //delay(1000);
    lightsOn(300, 1, 0, 0);
    lightsOn(300, 0, 1, 0);
    lightsOn(300, 0, 0, 1);
  }
}

void waddleLeftBwd() {
  rightStop();
  leftBwd();
  //delay(300);
  lightsOn(300, 1, 0, 0);
  leftStop();
  rightBwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  rightStop();
  leftBwd();
  //delay(300);
  lightsOn(300, 0, 0, 1);
  leftStop();
  rightBwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  rightStop();
}

void waddleRightBwd() {
  leftStop();
  rightBwd();
  //delay(300);
  lightsOn(300, 1, 0, 0);
  rightStop();
  leftBwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  leftStop();
  rightBwd();
  //delay(300);
  lightsOn(300, 0, 0, 1);
  rightStop();
  leftBwd();
  //delay(300);
  lightsOn(300, 0, 1, 0);
  leftStop();
}


// PRIMITIVES


int direction = 0;
int rightFwdSpeed = 128;
int leftFwdSpeed = 128;
int rightBwdSpeed = 128;
int leftBwdSpeed = 128;



void powerStop() {
  if (direction > 0) {
    bwdSpeed(FULL);
    bwd(200);
  }
  else if (direction < 0) {
    fwdSpeed(FULL);
    fwd(200);
  }
  stop();
  direction = 0;
  fwdSpeed(SLOW);
  bwdSpeed(SLOW);
}

void stop() {
  leftStop();
  rightStop();
  direction = 0;
}

void fwd(int t) {
  Serial.println("fwd()");
  rightFwd();
  leftFwd();
  direction = 1;
  if (t > 0) {
    delay(t);
    rightStop();
    leftStop();
    direction = 0;
  }
}

void bwd(int t) {
  Serial.println("bwd()");
  rightBwd();
  leftBwd();
  direction = -1;
  if (t > 0) {
    delay(t);
    rightStop();
    leftStop();
    direction = 0;
  }
}

void spinLeft(int t) {
  Serial.println("spinLeft()");
  rightFwd();
  leftBwd();
  delay(t);
  rightStop();
  leftStop();
}

void spinRight(int t) {
  Serial.println("spinRight()");
  leftFwd();
  rightBwd();
  delay(t);
  rightStop();
  leftStop();
}

void reverseDirection() {
  if (direction < 0) {
    fwd(10);
  }
  else {
    bwd(10);
  }
}

const int rightFwdCalibration = 0;
const int leftFwdCalibration = 0;
const int speedIncr = 10;

void fwdFaster() {
  if (rightFwdSpeed > FULL || leftFwdSpeed > FULL) {
    // do nothing
  }
  else if (direction > 0) {
    leftFwdSpeed -= speedIncr;
    rightFwdSpeed += speedIncr;
    fwd(0);
  }
  else if (direction < 0) {
    if (leftBwdSpeed > SLOW) {
      leftBwdSpeed += speedIncr;
      rightBwdSpeed -= speedIncr;
      bwd(0);
    }
    else {
      fwdSpeed(SLOW);
      fwd(0);
    }
  }
  else {
    fwdSpeed(SLOW);
    fwd(0);
  }
}

void bwdFaster() {
  if (rightBwdSpeed > FULL || leftBwdSpeed > FULL) {
    // do nothing
  }
  else if (direction > 0 && rightFwdSpeed > SLOW) {
    if (leftBwdSpeed > SLOW) {
      bwdSpeed(SLOW);
      bwd(0);
    }
    else {
      leftFwdSpeed += speedIncr;
      rightFwdSpeed -= speedIncr;
      fwd(0);
    }
  }
  else if (direction < 0) {
    leftBwdSpeed -= speedIncr;
    rightBwdSpeed += speedIncr;
    bwd(0);
  }
  else {
    bwdSpeed(SLOW);
    bwd(0);
  }
}

void fwdSpeed(int n) {
  Serial.println("fwdSpeed");
  leftFwdSpeed = 255 - n + leftFwdCalibration;
  rightFwdSpeed = n - rightFwdCalibration;
  Serial.println(leftFwdSpeed);
  Serial.println(rightFwdSpeed);
}

void leftFwd() {
  Serial.println("leftFwd()");
  Serial.println(leftFwdSpeed);
  analogWrite(PIN_MTR_L1, leftFwdSpeed);
  digitalWrite(PIN_MTR_L2, HIGH);
  digitalWrite(PIN_MTR_EN, HIGH);
}

void rightFwd() {
  Serial.println("rightFwd()");
  Serial.println(rightFwdSpeed);
  analogWrite(PIN_MTR_L3, rightFwdSpeed);
  digitalWrite(PIN_MTR_L4, LOW);
  digitalWrite(PIN_MTR_EN, HIGH);
}

const int leftBwdCalibration = 0;
const int rightBwdCalibration = -20;

void bwdSpeed(int n) {
  rightBwdSpeed = n + leftBwdCalibration;
  leftBwdSpeed = 255 - n - rightFwdCalibration;
}



void leftBwd() {
  Serial.println("leftBwd()");
  analogWrite(PIN_MTR_L1, rightBwdSpeed);
  digitalWrite(PIN_MTR_L2, LOW);
  digitalWrite(PIN_MTR_EN, HIGH);
}


void rightBwd() {
  Serial.println("leftBwd()");
  analogWrite(PIN_MTR_L3, leftBwdSpeed);
  digitalWrite(PIN_MTR_L4, HIGH);
  digitalWrite(PIN_MTR_EN, HIGH);
}

void leftStop() {
  digitalWrite(PIN_MTR_L1, LOW);
  digitalWrite(PIN_MTR_L2, LOW);
}

void rightStop() {
  digitalWrite(PIN_MTR_L3, LOW);
  digitalWrite(PIN_MTR_L4, LOW);
}

void lightsOn(int t, int r, int g, int b) {
  if (r != 0) digitalWrite(PIN_LED_R, HIGH);
  if (g != 0) digitalWrite(PIN_LED_G, HIGH);
  if (b != 0) digitalWrite(PIN_LED_B, HIGH);
  digitalWrite(PIN_LED_R, LOW);
  digitalWrite(PIN_LED_G, LOW);
  digitalWrite(PIN_LED_B, LOW);
  delay(t);
}

void recordImage() {
  digitalWrite(PIN_CAM_PWR, HIGH);
  delay(1000);
  digitalWrite(PIN_CAM_PWR, LOW);
}

void recordSound() {
  digitalWrite(PIN_AUD_R, HIGH);
}

void stopSound() {
  digitalWrite(PIN_AUD_R, LOW);
}

void playSound() {
  digitalWrite(PIN_AUD_P, HIGH);
  delay(500);
  digitalWrite(PIN_AUD_P, LOW);  
}

boolean bwdBump() {
  int in = digitalRead(PIN_BMP_R);
  if (in) {
    Serial.println("bwdBump");
    delay(1000);
    reverseDirection();
  }
  return in;
}

boolean fwdBump() {
  int in = digitalRead(PIN_BMP_F);
  if (in) {
    Serial.println("fwdBump");
    delay(1000);
    reverseDirection();
  }
  return in;
}


