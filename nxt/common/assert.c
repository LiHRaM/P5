#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "../inc/assert.h"
#include "../inc/lcd.h"

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