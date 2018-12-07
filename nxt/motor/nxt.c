/**
 * This code tests the motor component of the SUD.
 * A motor is expected to be plugged into PORT A of the NXT.
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* The motors should be able to rock 1000 times without any damage to the structure. */
#define ITERATIONS 1000
#define POWER 64

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{ /* do nothing */
}

void rotate(S8 speed)
{
	ecrobot_set_motor_speed(NXT_PORT_A, speed);
}

/**
 * The LCD display is 16 wide, 8 tall
 * x = range(0 to 15)
 * y = range(0 to 7)
 */
void print_iteration(int i)
{
	display_clear(0); /* 0: Do not update display as well */
	display_goto_xy(0, 3);
	display_string("Iter: ");
	display_goto_xy(5, 3);
	display_int(i, 4);
	display_update();
}

TASK(MainTask)
{
	for(int i = 0; i < ITERATIONS; i++) {
		print_iteration(i);
		rotate(POWER);
		systick_wait_ms(500);
		rotate(-POWER);
		systick_wait_ms(500);
	}
	rotate(0);
	TerminateTask();
}
