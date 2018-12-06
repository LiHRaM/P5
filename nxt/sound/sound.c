/**
 * This code tests the sound recording capabilities of the Lego NXT
 * Sound is transferred via bluetooth.
 * Author: 	Hilmar Gústafsson
 * Email: 	hgusta16@student.aau.dk
 */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define BUF_SIZE 128

static char rx_buf[BUF_SIZE];

/* OSEK declarations */
DeclareCounter(SysTimerCnt);

DeclareTask(FillBuffer);
DeclareTask(EmptyBuffer);

DeclareEvent(BufferFullEvent);

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
void user_1ms_isr_type2(void)
{
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
    if (ercd != E_OK)
    {
        ShutdownOS(ercd);
    }
}

/* FillBuffer executed every 1msec */
TASK(FillBuffer)
{
    static U8 i;
    rx_buf[i++] = ecrobot_get_sound_sensor(NXT_PORT_S1);
    if (i == 0) {
        SetEvent(EmptyBuffer, BufferFullEvent);
    }
    TerminateTask();
}

TASK(EmptyBuffer)
{
    while(1)
    {
        WaitEvent(BufferFullEvent);
        ClearEvent(BufferFullEvent);
        ecrobot_send_bt(rx_buf, 0, BUF_SIZE);
    }

    TerminateTask();
}