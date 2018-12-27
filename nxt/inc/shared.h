#ifndef __NXT_SHARED_H__
#define __NXT_SHARED_H__

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#ifndef GATHER_WAIT
#define GATHER_WAIT systick_wait_ns(18000);
#endif

void sanity_check(const char *str);
void fill_buffer(U16 *payload, U16 len);
void send_buffer(U16 *payload);
void set_all_speed(S8 speed);
void await_response();

#undef assert
void assert(int expression, const char *msg);
#endif /* !__NXT_SHARED_H__ */