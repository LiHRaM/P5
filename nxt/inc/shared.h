#ifndef __NXT_SHARED_H__
#define __NXT_SHARED_H__

typedef unsigned char RXBUF[256];

/**
 * As the sound sensor deals in 16 bit values, divide by 8 to fit into smaller spaces.
 * This sacrifices some accuracy, but saves us trouble.
 **/
unsigned char reduce_u16_to_u8(int value)
{
    return (1023 - value) / 8;
}

#endif