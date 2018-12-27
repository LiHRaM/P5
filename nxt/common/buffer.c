#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "../inc/buffer.h"

#ifndef GATHER_WAIT
#define GATHER_WAIT systick_wait_ns(18000);
#endif

/**
 * fill_buffer
 * 
 * Bounded to 16B
 * 
 **/
void fill_buffer(U16 *payload, U16 len)
{
    U16 i;
    for (i = 0; i < len; i++)
    {
        payload[i] = ecrobot_get_sound_sensor(NXT_PORT_S1);
        GATHER_WAIT
    }
}

/**
 * send_buffer
 * 
 * Bounded to 30B
 */
void send_buffer(U16 *payload)
{
    U16 sent = 0;
    while (sent < 256)
    {
        sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
    }
}

// Receive 1 byte via Bluetooth
void recv_buffer(U8 *payload)
{
    while (ecrobot_read_bt(payload, 0, 1) == 0)
        ;
}