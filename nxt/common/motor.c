#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "../inc/motor.h"

/**
 * set_all_speed
 * 
 * Bounded to 27B 
 **/
void set_all_speed(S8 speed)
{
    ecrobot_set_motor_speed(NXT_PORT_A, speed);
    ecrobot_set_motor_speed(NXT_PORT_B, speed);
    ecrobot_set_motor_speed(NXT_PORT_C, speed);
}