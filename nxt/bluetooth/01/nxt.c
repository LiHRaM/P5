/**
 * Testing the packet retention of different bluetooth strategies
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

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
 * This is the naive approach. For each "reading", it attempts to send a packet.
 **/
TASK(MainTask)
{
    static U16 i;
    static U16 payload[1];

    for (i = 0; i < 128; i++)
    {
        payload[0] = i;
        ecrobot_send_bt(payload, 0, 2);
    }
    TerminateTask();
}