

#include "Pack.h"
#include <arpa/inet.h> //htons
#include <string.h> //memcpy





///1 bytes


size_t readBYTE(const void *buf, uint8 *value)
{
    value[0] = *(uint8 *)buf;
    return 1;
}

size_t writeBYTE(void *buf, uint8 value)
{
    *(uint8 *)buf = value;
    return 1;
}


///2 bytes

size_t readUINT16(const void *network_buf, uint16 *value)
{
    value[0] = ntohs(*(uint16*)network_buf);
    return 2;
}


size_t writeUINT16(void *network_buf, uint16 value)
{
    *(uint16*)network_buf = htons(value);
    return 2;
}


size_t writeRawUINT16(void *host_buf, uint16 value)
{
    *(uint16*)host_buf = value;
    return 2;
}

size_t readRawUINT16(const void *host_buf, uint16 *value)
{
    value[0] = *(uint16*)host_buf;
    return 2;
}




///4 bytes


size_t readUINT32(const void *network_buf, uint32 *value)
{
    value[0] = ntohl(*(uint32*)network_buf);
    return 4;
}

size_t writeUINT32(void *network_buf, uint32 value)
{
    *(uint32*)network_buf = htonl(value);
    return 4;
}

size_t readRawUINT32(const void *host_buf, uint32 *value)
{
    value[0] = *(uint32*)host_buf;
    return 4;
}

size_t writeRawUINT32(void *host_buf, uint32 value)
{
    *(uint32*)host_buf = value;
    return 4;
}


///8 bytes

size_t readUINT64(const void *network_buf, uint64 *value)
{
    value[0] = ntohll(*(uint64*)network_buf);
    return 8;
}

size_t writeUINT64(void *network_buf, uint64 value)
{
    *(uint64*)network_buf = htonll(value);
    return 8;
}


size_t readRawUINT64(const void *host_buf, uint64 *value)
{
    value[0] = *(uint64*)host_buf;
    return 8;
}

size_t writeRawUINT64(void *host_buf, uint64 value)
{
    *(uint64*)host_buf = value;
    return 8;
}




/**变长字节类型
@see https://nlp.stanford.edu/IR-book/html/htmledition/variable-byte-codes-1.html
 
       bit1             bit2~8
 continuation bit        payload
 
 continuation bit
 
 we read a sequence of bytes with continuation bit 1 terminated by a byte with continuation bit 0
 We then extract and concatenate the 7-bit parts.
 @return readed bytes
 */
size_t readVINT(const void *network_buf, uint64 *vint)
{
    int byte_index = 0;
    uint64_t collect = 0;
    unsigned char curr_byte;

    do{
        curr_byte = ((uint8*)network_buf)[byte_index];

        uint64_t payload = curr_byte & 0b01111111;

        collect += payload << (byte_index * 7);

        byte_index += 1;

    }while ( curr_byte >= 0b10000000 );

    vint[0] = collect;

    return byte_index;
}


//变长整数,  把vint 化为 变长整数，写入buff,return: writed bytes
size_t writeVINT(void *network_buf, uint64 vint)
{
    int pos = 0;
    while (vint >= 0x80)
    {
        unsigned char t = 0x80 + vint % 0x80;
        ((uint8*)network_buf)[pos] = t;
        pos++;
        
        vint /= 0x80;
    }
    
    
    unsigned char t = vint % 0x80;
    ((uint8*)network_buf)[pos] = t;
    pos++;
    
    return pos;
}







    







    

size_t readRaw(const void *host_buff, void *rawBytes, size_t len)
{
    memcpy(rawBytes, host_buff, len);
    return len;
}


size_t writeRaw(void *host_buff, const void *rawBytes, size_t len)
{
    memcpy(host_buff, rawBytes, len);
    return len;
}

void pack_test(void)
{

}


