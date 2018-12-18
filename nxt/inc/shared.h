#ifndef __NXT_SHARED_H__
#define __NXT_SHARED_H__

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#ifndef GATHER_WAIT
#define GATHER_WAIT systick_wait_ns(18000);
#endif

/**
 *  Helper function for checking whether the memory has been exceeded.
 **/
void sanity_check(const char *str)
{
    display_clear(0);
    display_goto_xy(0, 0);
    display_string(str);
    display_update();
}

/**
 * fill_buffer
 * 
 * Space complexity:
 * *payload     = 4 bytes
 * len          = 2 bytes
 * i            = 2 bytes
 * 
 * 8 bytes
 * 
 * systick_wait_ms  worst case complexity:
 * ecrobot_get_s... worst case complexity:
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
 * sent = 2 bytes
 */
void send_buffer(U16 *payload)
{
    U16 sent = 0;
    while (sent < 256)
    {
        sent += ecrobot_send_bt(payload + (sent / 2), 0, 256 - sent);
    }
}

/**
 * set_all_speed
 * speed = 1 byte
 * 
 * ecrobot_set_motor_speed worst case complexity: 
 **/
void set_all_speed(S8 speed) {
    ecrobot_set_motor_speed(NXT_PORT_A, speed);
    ecrobot_set_motor_speed(NXT_PORT_B, speed);
    ecrobot_set_motor_speed(NXT_PORT_C, speed);
}

/**
 * await_response
 * payload          = 1 byte
 * timer            = 1 byte
 * 
 * ecrobot_read_bt  = 4 bytes
 * 
 **/
void await_response()
{
    static U8 payload[1]; 
    static U8 timer;

    while(ecrobot_read_bt(payload, 0, 1) == 0)
        ;

    if (payload[0] == 1)
    {
        for(timer = 0; timer < 10; timer++) {
            set_all_speed(60);
            systick_wait_ms(500);
            set_all_speed(-60);
            systick_wait_ms(500);
        }
        set_all_speed(0);
    }
}

#undef assert
void assert(int expression, const char *msg)
{
    if (expression)
    {
        return;
    }
    else
    {
        sanity_check(msg);
        TerminateTask();
    }
}
#endif