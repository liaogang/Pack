/*
 * all functions return number of bytes writed or readed
 */
#include "defs.h"
#include <stdio.h>

#ifndef Pack_h
#define Pack_h

#ifdef __cplusplus
extern "C" {
#endif



///1 bytes

size_t readBYTE(const void *buf, uint8 *value);
size_t writeBYTE(void *buf, uint8 value);


///2 bytes


size_t readUINT16(const void *network_buf, uint16 *value);
size_t writeUINT16(void *network_buf, uint16 value);

size_t readRawUINT16(const void *host_buf, uint16 *value);
size_t writeRawUINT16(void *host_buf, uint16 value);


///4 bytes


size_t readUINT32(const void *network_buf, uint32 *value);
size_t writeUINT32(void *network_buf, uint32 value);

size_t readRawUINT32(const void *host_buf, uint32 *value);
size_t writeRawUINT32(void *host_buf, uint32 value);


///8 bytes

size_t readUINT64(const void *network_buf, uint64 *value);
size_t writeUINT64(void *network_buf, uint64 value);

size_t readRawUINT64(const void *host_buf, uint64 *value);
size_t writeRawUINT64(void *host_buf, uint64 value);


///variable int @see https://nlp.stanford.edu/IR-book/html/htmledition/variable-byte-codes-1.html


size_t readVINT(const void *network_buf, uint64 *vint);
size_t writeVINT(void *network_buf, uint64 vint);


///multi bytes or string


size_t writeRaw(void *host_buf, const void *rawBytes, size_t len);
size_t readRaw(const void *host_buff, void *rawBytes, size_t len);


//write key string and value buffer
size_t writeKV(uint8 *buffer,
                     const uint8 *keybuf,
                     unsigned int keylen,
                     const uint8 *valuebuf,
                     unsigned int valuelen);

//write key string and value string
size_t writeKVString(uint8 *buffer, const char *keyString, const char *valueString);

void pack_test(void);


#ifdef __cplusplus
}
#endif

#endif /* Pack_h */
