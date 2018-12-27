#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "../inc/logic.h"
#include "../inc/motor.h"
#include "../inc/buffer.h"

/**
 * await_response
 * 
 * Bounded to 38B
 **/
void await_response()
{
    static U8 payload[1];
    static U8 timer;

    recv_buffer(payload);

    if (payload[0] == 1)
    {
        for (timer = 0; timer < 10; timer++)
        {
            set_all_speed(60);
            systick_wait_ms(500);
            set_all_speed(-60);
            systick_wait_ms(500);
        }
        set_all_speed(0);
    }
}