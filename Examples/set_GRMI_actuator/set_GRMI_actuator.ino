/*
  * Example using the GRMI_actuator Library
  * By: Juan S. Cely G.
  * GRMI - Research Group
  * Underwater Robotics Lab.
  * Nov. 2020
*/

#include <GRMI_actuator.h> // Import the library

GRMI_actuator base(0);
GRMI_actuator gripper(1);

void setup(){
  base.begin();
  gripper.begin();
}

void loop(){
  base.open(base.time_step);
  gripper.open(gripper.time_step);
  delay(5000);
  gripper.close(gripper.time_step);  
  base.close(base.time_step);
  }
