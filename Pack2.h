/*
 *
 * If function name contain Raw, the param buf is in host
 * else the buffer is in network (Big endian)
 *
 * return number of bytes writed or readed
 */


#include "defs.h"
#include <stdio.h>

#ifndef Pack2_h
#define Pack2_h



///3 bytes, use uint32 ignore the mostest significant byte

size_t readUINT24(const void *network_buf, uint32 *value);
size_t writeUINT24(void *network_buf, uint32 value);

size_t readRawUint24(void *host_buf, uint32 *value);
size_t writeRawUint24(void *host_buf, uint32 value);

void pack2_test(void);

#endif /* Pack2_h */