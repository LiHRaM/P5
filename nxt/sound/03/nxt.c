/**
 * Different timing strategies for audio recording snippets
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "shared.h"

/* nxtOSEK hooks */
void ecrobot_device_initialize()
{
    ecrobot_init_bt_slave("LEiOS-OSEK");
}

void ecrobot_device_terminate()
{
    ecrobot_term_bt_connection();
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {}

/**
 * Fill the buffer 128 times, and see how much time has passed.
 **/
TASK(MainTask)
{
    sanity_check("Loading buffer...");
    static U16 payload[128];

    /* Assertions */
    assert(sizeof(payload) == 256, "buf != 256");
    
    /* 16.384 samples in all */
    for(int i = 0; i < 128; i++) {
        for (unsigned char i = 0; i < 128; i++)
        {
            payload[i] = ecrobot_get_sound_sensor(NXT_PORT_S1);
            systick_wait_ns(18000);
        }
    }

    assert(payload[0] != 0, "buf[0] != 0");
    
    /* Measure the execution time of transmitting the buffer */
    U32 rename = systick_get_ms();
    transmit_buffer(payload);
    rename = systick_get_ms() - rename;

    sanity_check("Task complete...");

    display_goto_xy(0, 3);
    display_int(rename, 5);
    display_update();

    TerminateTask();
}