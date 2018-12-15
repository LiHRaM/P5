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

    /* Assertions */
    assert(sizeof(payload) == 256);
    
    for(int j = 0; j < 128; j++) {
        for (unsigned char i = 0; i < 128; i++)
        {
            payload[i] = ecrobot_get_sound_sensor(NXT_PORT_S1);
            systick_wait_ns(62500); // 16 samples pr second
        }

        sanity_check("Sending over BT...");

        U16 sent = 0;
        while(sent < 256) {
            sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
            systick_wait_ms(1);
        }
    }

    sanity_check("Task complete...");

    TerminateTask();
}