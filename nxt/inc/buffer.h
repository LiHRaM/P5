#ifndef LiHRaM_BUFFER_H
#define LiHRaM_BUFFER_H

#include "mytypes.h"

void fill_buffer(U16 *payload, U16 len);
void send_buffer(U16 *payload);
void recv_buffer(U8 *payload);

#endif /* !LiHRaM_BUFFER_H */