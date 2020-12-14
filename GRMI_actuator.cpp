/*
GRMI_actuator.cpp - Library for GRMI electro hydraulic actuator
Created by Juan S. Cely, Nov 2020
GRMI CAR UPM CSIC
*/

/// header files
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <digitalWriteFast.h>
#include <GRMI_actuator.h>

GRMI_actuator::GRMI_actuator(int mode){
  _mode = mode;
  if(_mode==0){
    pinModeFast(motorA_ena_pin, OUTPUT);
    pinModeFast(motorA_dir_pin, OUTPUT);
    pinModeFast(motorA_clk_pin, OUTPUT);
    pinModeFast(motorA_high_pin, INPUT);
    pinModeFast(motorA_low_pin, INPUT);
  }
  else if(_mode==1){
    pinModeFast(motorB_ena_pin, OUTPUT);
    pinModeFast(motorB_dir_pin, OUTPUT);
    pinModeFast(motorB_clk_pin, OUTPUT);
    pinModeFast(motorB_high_pin, INPUT);
    pinModeFast(motorB_low_pin, INPUT);
  }
  else{
    _mode=0;
    pinModeFast(motorA_ena_pin, OUTPUT);
    pinModeFast(motorA_dir_pin, OUTPUT);
    pinModeFast(motorA_clk_pin, OUTPUT);
    pinModeFast(motorA_high_pin, INPUT);
    pinModeFast(motorA_low_pin, INPUT);
  }
}

void GRMI_actuator::begin(){
  close(time_step);
}

void GRMI_actuator::enable(){
  ena_state = HIGH;
  if(_mode==1){digitalWriteFast(motorB_ena_pin, !ena_state);}
  else{digitalWriteFast(motorA_ena_pin, !ena_state);}
}

void GRMI_actuator::disable(){
  ena_state = LOW;
  if(_mode==1){digitalWriteFast(motorB_ena_pin, !ena_state);}
  else{digitalWriteFast(motorA_ena_pin, !ena_state);}
}

void GRMI_actuator::set_direction(byte dir){
  if(_mode==1){digitalWriteFast(motorB_dir_pin, dir);}
  else{digitalWriteFast(motorA_dir_pin, dir);}
}

void GRMI_actuator::get_limits(){
  if(_mode==0){
    high_state = digitalReadFast(motorA_high_pin);
    low_state = digitalReadFast(motorA_low_pin);
  }
  if(_mode==1){
    high_state = digitalReadFast(motorB_high_pin);
    low_state = digitalReadFast(motorB_low_pin);
  }

}

void GRMI_actuator::move(int t_step){
  if(_mode==0){
    digitalWriteFast(motorA_clk_pin, HIGH);
    delayMicroseconds(t_step);
    digitalWriteFast(motorA_clk_pin, LOW);
    delayMicroseconds(t_step);
  }
  if(_mode==1){
    digitalWriteFast(motorB_clk_pin, HIGH);
    delayMicroseconds(t_step);
    digitalWriteFast(motorB_clk_pin, LOW);
    delayMicroseconds(t_step);
  }
  get_limits();
}

void GRMI_actuator::set_inside(int t_step){
  set_direction(Inside);
  enable();
  while(!low_state){
    move(t_step);
  }
  disable();
}

void GRMI_actuator::set_outside(int t_step){
  set_direction(Outside);
  enable();
  while(!high_state){
    move(t_step);
  }
  disable();
}

void GRMI_actuator::open(int t_step){
  if (_mode==1){set_inside(t_step);}
  else{set_outside(t_step);}
}

void GRMI_actuator::close(int t_step){
  if (_mode==1){set_outside(t_step);}
  else{set_inside(t_step);}
}
