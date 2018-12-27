/**
 * Code for generating an NXT dataset.
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define GATHER_WAIT systick_wait_ms(1);
#include "logic.h"
#include "buffer.h"

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
 * MainTask
 * 
 * Bounded to 295B
 **/
TASK(MainTask)
{
    static U16 payload[128];
    S8 i;
    
    while(1)
    {
        for(i = 0; i < 5; i++) {
            fill_buffer(payload, 128);
            send_buffer(payload);
        }
        await_response();
    }
}