/**
 * Testing the packet retention of different bluetooth strategies
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
    
    for (unsigned char i = 0; i < 128; i++)
    {
        payload[i] = i;
    }

    sanity_check("Sending over BT...");

    for(int j = 0; j < 2; j++) {
        U16 sent = 0;
        while(sent < 256) {
            sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
            display_clear(0);
            display_goto_xy(0, 1);
            display_int(sent, 4);
            display_update();
            systick_wait_ms(1);
        }
    }

    sanity_check("Task complete...");

    TerminateTask();
}