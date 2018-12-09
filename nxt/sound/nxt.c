/**
 * This is a modification of the bluetooth test,
 * where the buffer entries are replaced with the sensor recordings.
 * 
 * It assumes the sound sensor is plugged into sensor port 1.
 * 
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */
/* nxtOSEK */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* user files */
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

/**
 * Fetch sound sensor value and compress it.
 */
U8 read_sound() {
    return reduce_u16_to_u8(ecrobot_get_sound_sensor(NXT_PORT_S1));
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
    static RXBUF rx_buf;

    // Repeat forever
    while(1) {
        for (i = 0; i < BUF_SIZE; i++)
        {
            rx_buf[i] = read_sound();
            systick_wait_ms(1);
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
    }
    TerminateTask();
}