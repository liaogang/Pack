//
// Created by apple  on 2021/12/2.
//

#include "Pack2.h"
#include <arpa/inet.h> //htons
#include <assert.h>


int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}


///3 bytes


size_t readUINT24(const void *network_buf, uint32 *value)
{
    assert( is_big_endian());

    //(ignored buf -1) buf0 buf1 buf2
    //sigbig sig mid sig small

    uint8 fix[4];
    fix[0] = 0;
    fix[1] = ((uint8*)network_buf)[0];
    fix[2] = ((uint8*)network_buf)[1];
    fix[3] = ((uint8*)network_buf)[2];

    value[0] = ntohl(*(uint32*)fix);

    return 3;
}

size_t writeUINT24(void *network_buf, uint32 value)
{
    assert( is_big_endian());

    uint8 fix[4];
    *(uint32*)fix = htonl(value);//to big-endian

    //big-endian,  (ignored fix 0) fix1 fix2 fix3

    ((uint8*)network_buf)[0] = fix[1];
    ((uint8*)network_buf)[1] = fix[2];
    ((uint8*)network_buf)[2] = fix[3];

    return 3;
}



size_t readRawUint24(void *host_buf, uint32 *value)
{
    assert( is_big_endian());

    //buf0 buf1 buf2 (ignored buf 3)
    //sigbig sig mid sig small
    uint8 fix[4];
    fix[0] = ((uint8*)host_buf)[0];
    fix[1] = ((uint8*)host_buf)[1];
    fix[2] = ((uint8*)host_buf)[2];
    fix[3] = 0;

    value[0] = *(uint32*)fix;

    return 3;
}


size_t writeRawUint24(void *host_buf, uint32 value)
{
    assert( is_big_endian());

    uint8 fix[4];

    *(uint32*)fix = value;

    //little-endian, fix0 fix1 fix2 (ignored fix 3)

    ((uint8*)host_buf)[0] = fix[0];
    ((uint8*)host_buf)[1] = fix[1];
    ((uint8*)host_buf)[2] = fix[2];

    return 3;
}