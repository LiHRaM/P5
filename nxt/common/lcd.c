#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "../inc/lcd.h"

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