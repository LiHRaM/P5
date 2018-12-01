/**
 * Author: Hilmar Gústafsson
 * The robot detects the cries of children and rocks a cradle accordingly.
 */

#define SAMPLES 256
#define ROCK_DURATION 60

// ECRobot++ API
#include "SoundSensor.h"
#include "Motor.h"
#include "Port.h"
#include "Clock.h"
#include "Lcd.h"

using namespace ecrobot;

extern "C" {
	#include "kernel.h"
	#include "kernel_id.h"
	#include "ecrobot_interface.h"

	// Firmware objects
	Clock clock;
	Lcd lcd;
	// Motor M2(PORT_B);
	// Motor M3(PORT_C);
	SoundSensor mic(PORT_2);

	/* nxtOSEK hook to be invoked from an ISR in category 2 */
	void user_1ms_isr_type2(void) {
		SleeperMonitor(); // needed for I2C device and Clock classes
	}

	bool is_cry(void) {
		// TODO: Analyze the buffer (consider it immutable)
		return true;
	}

	TASK(TaskMain) {
		U8 counter = 0;
		// TODO: Print initial message
		
		while (true) {
			lcd.clear();
			while(counter > 0) {
				// TODO: Rock back and forth
				ecrobot_set_motor_speed(PORT_A, 64);
				ecrobot_set_motor_speed(PORT_B, 64);
				ecrobot_set_motor_speed(PORT_C, 64);
				clock.wait(500);
				ecrobot_set_motor_speed(PORT_A, -64);
				ecrobot_set_motor_speed(PORT_B, -64);
				ecrobot_set_motor_speed(PORT_C, -64);
				clock.wait(500);
				counter--;
			}

			for(int i = 0; i < SAMPLES; i++) {
				// Fill buffer
			}

			/**
			 * TODO: Pre-process data
			 * NOTE: Operations are performed in-place, to preserve memory.
			 */


			// Perform analysis
			if (is_cry()) {
				lcd.clear();
				lcd.putf("sn", "Cry detected...");
				lcd.disp();
				clock.wait(1000);
				counter = ROCK_DURATION;
			}
		}
	}
}
