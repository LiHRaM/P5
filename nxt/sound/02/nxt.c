/**
 * Testing the packet retention of different sound recording strategies
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include <assert.h>
#include "shared.h"

/* nxtOSEK hooks */
void ecrobot_device_initialize()
{
    ecrobot_init_bt_slave("LEJOS-OSEK");
}

void ecrobot_device_terminate()
{
    ecrobot_term_bt_connection();
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {}

/**
 * This is the second approach. Fill a buffer, and then send every item of the buffer.
 * Still using U16 datatype.
 **/
TASK(MainTask)
{
    sanity_check("Loading buffer...");
    static U16 payload[128];
    U32 base_time = systick_get_ms();

    /* Assertions */
    assert(sizeof(payload) == 256);
    
    for(int j = 0; j < 128; j++) {
        for (unsigned char i = 0; i < 128; i++)
        {
            payload[i] = ecrobot_get_sound_sensor(NXT_PORT_S1);
            systick_wait_ns(31250); // 1/32th of a second
        }

        sanity_check("Sending over BT...");

        U16 sent = 0;
        while(sent < 256) {
            sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
            systick_wait_ns(31250); // Wait as long as sample size
        }
    }

    base_time = systick_get_ms() - base_time;

    sanity_check("Task complete...");

    display_goto_xy(0, 3);
    display_int(base_time, 5);
    display_update();

    TerminateTask();
}