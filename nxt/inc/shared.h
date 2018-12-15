#ifndef __NXT_SHARED_H__
#define __NXT_SHARED_H__

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


/**
 *  Helper function for checking whether the memory has been exceeded.
 **/
void sanity_check(const char* str)
{
    display_clear(0);
    display_goto_xy(0,0);
    display_string(str);
    display_update();
}

/* Fill a buffer at 16KHz */
void fill_buffer(U16 *payload, U16 len) {
    for (unsigned char i = 0; i < len; i++)
    {
        payload[i] = ecrobot_get_sound_sensor(NXT_PORT_S1);
        systick_wait_ns(18000);
    }
}

/* Send the buffer via Bluetooth */
void transmit_buffer(U16 *payload) {
    U16 sent = 0;
    while(sent < 256) {
        sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
        systick_wait_ns(18000);
    }
}

#undef assert
void assert(int expression, const char *msg) {
    if (expression) {
        return;
    } else {
        sanity_check(msg);
        TerminateTask();
    }
}

#endif