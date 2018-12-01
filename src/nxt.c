/**
 * This is the code for a robot which detects the crying of children, and activates motors for rocking them.
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define SAMPLES 256
#define ROCK_DURATION 60

static int BUFFER [SAMPLES];
static int counter = 0;

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{ /* do nothing */
}

/* Device initialization */
void ecrobot_device_initialize(void)
{
    /* Initialize ECRobot used devices */
    ecrobot_init_bt_connection();
}

/* Device termination */
void ecrobot_device_terminate(void)
{
    /* Terminate ECRobot used devices */
	ecrobot_set_motor_speed(NXT_PORT_A, 0);
    ecrobot_set_motor_speed(NXT_PORT_B, 0);
    ecrobot_set_motor_speed(NXT_PORT_C, 0);
    ecrobot_term_bt_connection();
}

/**
 * The data is read into the buffer here.
 */
void read()
{
	for(int i = 0; i < SAMPLES; i++) {
		BUFFER[i] = 1023 - ecrobot_get_sound_sensor(NXT_PORT_S1);
	}
}

/**
 * The data is pre-processed here.
 */
void preprocess()
{
	
}

/**
 * The sound is analyzed here.
 */
int is_cry()
{
	return 1;
}

/**
 * Rotate all motors in the same direction at the same speed
 */
void rotate_all(S8 speed)
{
	ecrobot_set_motor_speed(NXT_PORT_A, speed);
	ecrobot_set_motor_speed(NXT_PORT_B, speed);
	ecrobot_set_motor_speed(NXT_PORT_C, speed);
}

TASK(MainTask)
{	
	while (1)
	{
		while (counter > 0)
		{
			rotate_all(64);
			systick_wait_ms(500);
			rotate_all(-64);
			systick_wait_ms(500);
			counter--;
		}

		read();

		preprocess();

		if (is_cry())
		{
			counter = ROCK_DURATION;
		}
	}
}
