/**
 * Author: Hilmar Gústafsson
 * The robot detects the cries of children and rocks a cradle accordingly.
 */

#define SAMPLES 256

// ECRobot++ API
#include "SoundSensor.h"
#include "Clock.h"
#include "Lcd.h"

using namespace ecrobot;

extern "C" {
	#include "kernel.h"
	#include "kernel_id.h"
	#include "ecrobot_interface.h"

	// Firmware objects
	Lcd lcd;
	SoundSensor mic(PORT_2);

	/* nxtOSEK hook to be invoked from an ISR in category 2 */
	void user_1ms_isr_type2(void) {
		SleeperMonitor(); // needed for I2C device and Clock classes
	}

	TASK(TaskMain) {
		/**
		 * Print initial message
		 * Start main loop
		 *  while counter is not zero:
		 *    rock back and forth
		 *    wait 1 second
		 * 	Start sound buffer loop
		 * 	  Fill sound buffer
		 * 	Detect cry
		 *    if sound is cry:
		 *       set counter to 60
		 */ 
	}
}
