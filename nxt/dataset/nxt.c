/**
 * Code for generating an NXT dataset.
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
    ecrobot_init_bt_slave("LEJOS-OSEK");
}

void ecrobot_device_terminate()
{
    ecrobot_term_bt_connection();
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {}

/**
 * Looping through and sending bluetooth, what is the maximum time elapsed sending the buffer?
 **/
TASK(MainTask)
{
    static U16 payload[128];

    /* Assertions */
    assert(sizeof(payload) == 256, "buf != 256");

    /* Continue until stopped. */
    while(1) {
        fill_buffer(payload, 128);
        send_buffer(payload);
    }
}