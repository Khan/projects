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

#ifndef Bitzee_h
#define Bitzee_h

#include <Arduino.h>
#include <../IRRemote/IRremote.h>

// Code emitted by IR remote control
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


class Bitzee {

 private:

  // Arduino pins meanings
  static const int PIN_BMP_R = A5;
  static const int PIN_BMP_F = A4;
  static const int PIN_LED_G = A1;
  static const int PIN_LED_R = A0;
  static const int PIN_LED_B = A2;
  
  static const int PIN_CAM_IMG = 4;
  static const int PIN_AUD_R   = 2;
  static const int PIN_AUD_P   = 3;
  static const int PIN_CAM_PWR = 5;
  static const int PIN_RIR_RCV = 12;
  static const int PIN_FIR_RCV = 11;

  static const int PIN_MTR_EN  = 6;
  static const int PIN_MTR_L1  = 10;
  static const int PIN_MTR_L2  = 8;
  static const int PIN_MTR_L3  = 9;
  static const int PIN_MTR_L4  = 7;

 
 public:

  // Speed values
  static const int FULL;
  static const int SLOW;

  static IRrecv irrecv;
  static decode_results results;


  // Creating a Bit-zee instance
  Bitzee();

  // Controlling Bit-zee
  void forward();
  void forwardLeft();
  void forwardRight();
  void backward();
  void backwardLeft();
  void backwardRight();
  void coast();
  void coastLeft();
  void coastRight();
  void stop();
  void stopLeft();
  void stopRight();
  void speed(int n);
  void accelerate(int n);
  void decelerate(int n);
  void blinkLEDs(int t, int r, int g, int b);
  void recordImage();
  void recordSound();
  void playSound();

  // Calibrating Bit-zee's motors
  void calibrate(int values[]);

};

#endif // Bitzee.h
