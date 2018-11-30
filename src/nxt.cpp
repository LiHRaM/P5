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

	SoundSensor mic(PORT_2);

	unsigned int buffer[SAMPLES];

	/* nxtOSEK hook to be invoked from an ISR in category 2 */
	void user_1ms_isr_type2(void) {
		SleeperMonitor(); // needed for I2C device and Clock classes
	}

	TASK(TaskMain) {
		Clock clock;
		Lcd lcd;

		begin:
		for(int i = 0; i < SAMPLES; i++) {
			buffer[i] = mic.getLevel();
			lcd.clear();
			lcd.putf("sn", "NXT Sensors");
			lcd.putf("sdn", "Noise: ", buffer[i]);
			lcd.putf("sdn", "Sample: ", i);
			lcd.putf("sdn", "size: ", sizeof(clock));
			lcd.disp();
		}
//		goto begin;
	}
}
