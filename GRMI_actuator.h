/*
GRMI_actuator.h - Library for GRMI electro hydraulic actuator
Created by Juan S. Cely, Nov 2020
GRMI CAR UPM CSIC
*/

#ifndef GRMI_actuator_h
#define GRMI_actuator_h
/// header files
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <digitalWriteFast.h>

/// Define Variables
#define Inside LOW
#define Outside HIGH

// Motor A
#define motorA_ena_pin  4
#define motorA_dir_pin  5
#define motorA_clk_pin  6
#define motorA_high_pin  11
#define motorA_low_pin  2
// Motor B
#define motorB_ena_pin  8
#define motorB_dir_pin  9
#define motorB_clk_pin  10
#define motorB_high_pin  7
#define motorB_low_pin  3

/// Class Define
class GRMI_actuator{
public:
  //Methods
  GRMI_actuator(int);
  void begin(void);
  void enable(void);
  void disable(void);
  void set_direction(byte);
  void get_limits(void);
  void move(int);
  void close(int);
  void open(int);
  void set_outside(int);
  void set_inside(int);
  //Parameters
  byte ena_state = LOW;
  byte dir_state = LOW;
  byte high_state = LOW;
  byte low_state = LOW;

  int time_step = 1500;
private:
  int _mode=0;
};

#endif
