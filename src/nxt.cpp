/**
 * Author: Hilmar Gústafsson
 * The robot detects the cries of children and rocks a cradle accordingly.
 */

// ECRobot++ API
#include "Port.h"
#include "Clock.h"
#include "Lcd.h"

using namespace ecrobot;

static const U8 SAMPLES = 256;
static const U8 ROCK_DURATION = 60;
static const U8 CRY_THESHOLD = 80;

static U16 BUFFER [SAMPLES] = {};

extern "C" {
	#include "ecrobot_interface.h"

	Lcd lcd;
	Clock clock;

	/* nxtOSEK hook to be invoked from an ISR in category 2 */
	void user_1ms_isr_type2(void) {
		SleeperMonitor(); // needed for I2C device and Clock classes
	}

	/**
	 * The data is read into the buffer here.
	 */
	void read() {
		for(U8 i = 0; i < SAMPLES; i++) {
			BUFFER[i] = 1023 - ecrobot_get_sound_sensor(PORT_1);
		}
	}

	/**
	 * The data is pre-processed here.
	 */
	void preprocess() {
		// BUFFER[0] = 15;
	}

	/**
	 * The sound is analyzed here.
	 */
	bool is_cry(void) {
		// TODO: First, implement a bluetooth call to the computer, which performs the analysis
		// TODO: Second, use FastGRNN model to analyze the sample.

		return true;
	}

	TASK(TaskMain) {
		U8 counter = 0;
		// TODO: Print initial message
		
		while (true) {
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

			read();

			/**
			 * TODO: Pre-process data
			 * NOTE: Operations are performed in-place, to preserve memory.
			 */

			preprocess();
			
			// Perform analysis
			if (is_cry()) {
				lcd.clear();
				lcd.putf("sn", "Cry detected...");
				lcd.disp();
				counter = ROCK_DURATION;
			}
		}
	}
}
