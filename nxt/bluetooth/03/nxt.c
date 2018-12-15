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

#define BUF_SIZE 128

/**
 * Gather a buffer of 256 samples (assumed to be gathered in the equal amount of ms)
 * Send this buffer over bluetooth until it is sent entirely.
 */
TASK(MainTask)
{
    static U8 i;
    U8 rx_buf[BUF_SIZE]; // for a total of 256 bytes, which is the max allowed by ecrobot_send_bt

    for (i = 0; i < BUF_SIZE; i++)
    {
        rx_buf[i] = i;
    }

    /* Lock until the state is BT_STREAM */
    while (ecrobot_get_bt_status() != BT_STREAM)
        ; // spin

    /* Continue sending the same packet until everything has been received. */
    U8 sent = 0;
    while (sent < BUF_SIZE)
    {
        sent += ecrobot_send_bt(rx_buf + sent, 0, BUF_SIZE - sent);

        /* Hopefully we won't lose more than a few ms sending the packet. */
        systick_wait_ms(1);
    }
    systick_wait_ms(1);

    TerminateTask();
}