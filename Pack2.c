//
// Created by apple  on 2021/12/2.
//

#include "Pack2.h"
#include <arpa/inet.h> //htons
#include <assert.h>

/*
 * @see 字节顺序 https://zh.wikipedia.org/wiki/%E5%AD%97%E8%8A%82%E5%BA%8F#%E7%BD%91%E7%BB%9C%E5%BA%8F
 * 将一个多位数的低位放在较小的地址处，高位放在较大的地址处，则称小端序；反之则称大端序。
 * 网络传输一般采用大端序，也被称之为网络字节序，或网络序。IP协议中定义大端序为网络字节序。
*/

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
    if (is_big_endian())
    {
        ((uint8*)value)[0] = 0;
        ((uint8*)value)[1] = ((uint8*)network_buf)[0];
        ((uint8*)value)[2] = ((uint8*)network_buf)[1];
        ((uint8*)value)[3] = ((uint8*)network_buf)[2];

    }else{
        
        //(ignored buf -1) buf0 buf1 buf2
        //sigbig sig mid sig small

        ((uint8*)value)[0] = ((uint8*)network_buf)[2];
        ((uint8*)value)[1] = ((uint8*)network_buf)[1];
        ((uint8*)value)[2] = ((uint8*)network_buf)[0];
        ((uint8*)value)[3] = 0;
    }

    return 3;
}

size_t writeUINT24(void *network_buf, uint32 value)
{
    if (is_big_endian())
    {
        ((uint8*)network_buf)[0] = ((uint8*)&value)[1];
        ((uint8*)network_buf)[1] = ((uint8*)&value)[2];
        ((uint8*)network_buf)[2] = ((uint8*)&value)[3];
    }else{
        ((uint8*)network_buf)[0] = ((uint8*)&value)[2];
        ((uint8*)network_buf)[1] = ((uint8*)&value)[1];
        ((uint8*)network_buf)[2] = ((uint8*)&value)[0];
    }

    return 3;
}



size_t readRawUint24(void *host_buf, uint32 *value)
{
    if (is_big_endian())
    {
        //0x0a0b0c0d
        //           -1    0    1   2
        //host_buf (0x0a) 0x0b 0x0c 0x0d

        //                  0   1    2    3
        //value           0x00 0x0b 0x0c 0x0d

        //just offset 1
        ((uint8*)value)[0] = 0;
        ((uint8*)value)[1] = ((uint8*)host_buf)[0];//b
        ((uint8*)value)[2] = ((uint8*)host_buf)[1];//c
        ((uint8*)value)[3] = ((uint8*)host_buf)[2];//d
    }else{
        //0x0a0b0c0d
        //host_buf 0x0d 0x0c 0x0b | 0x0a
        //value  0x0d 0x0c 0x0b (0x00)


        ((uint8*)value)[3] = 0;//host_buf 3 -> a ignored
        ((uint8*)value)[2] = ((uint8*)host_buf)[2];//b
        ((uint8*)value)[1] = ((uint8*)host_buf)[1];//c
        ((uint8*)value)[0] = ((uint8*)host_buf)[0];//d
    }

    return 3;
}


size_t writeRawUint24(void *host_buf, uint32 value)
{
    if (is_big_endian())
    {
        //0x0a0b0c0d

        //                  0   1    2    3
        //value           0x0a 0x0b 0x0c 0x0d

        //           -1    0    1   2
        //host_buf (0x0a) 0x0b 0x0c 0x0d

        ((uint8*)host_buf)[0] = ((uint8*)&value)[1];//b
        ((uint8*)host_buf)[1] = ((uint8*)&value)[2];//c
        ((uint8*)host_buf)[2] = ((uint8*)&value)[3];//d
    }else{

        //0x0a0b0c0d
        //value    0x0d 0x0c 0x0b 0x0a
        //host_buf 0x0d 0x0c 0x0b

        ((uint8*)host_buf)[0] = ((uint8*)&value)[0];//d
        ((uint8*)host_buf)[1] = ((uint8*)&value)[1];//c
        ((uint8*)host_buf)[2] = ((uint8*)&value)[2];//b
    }

    return 3;
}


void pack2_test(void)
{
    if (is_big_endian())
    {
        uint32 value;
        ((uint8*)&value)[0] = 0x0a;
        ((uint8*)&value)[1] = 0x0b;
        ((uint8*)&value)[2] = 0x0c;
        ((uint8*)&value)[3] = 0x0d;
        
        assert(value == 0x0a0b0c0d);

        uint8 buff[3] = {0};
        writeUINT24(buff, value);


    }else {

        uint32 value;
        ((uint8 *) &value)[0] = 0x0d;
        ((uint8 *) &value)[1] = 0x0c;
        ((uint8 *) &value)[2] = 0x0b;
        ((uint8 *) &value)[3] = 0x0a;

        assert(value == 0x0a0b0c0d);

        ((uint8 *) &value)[3] = 0x00;//ignore the most big
        assert(value == 0x000b0c0d);

        uint8 network_buff[3] = {0};
        writeUINT24(network_buff, value);


        uint32 value2 = 0;
        readUINT24(network_buff, &value2);

        assert(value2 == value);


        {
            uint8 host_buff[3] = {0};
            writeRawUint24(host_buff, value);

            assert(host_buff[0] == network_buff[2]);
            assert(host_buff[1] == network_buff[1]);
            assert(host_buff[2] == network_buff[0]);

            uint8 host_buff2[4] = {0};
            writeRawUint24(host_buff2, value);
            assert(host_buff2[0] == host_buff[0]);
            assert(host_buff2[1] == host_buff[1]);
            assert(host_buff2[2] == host_buff[2]);
        }


        printf("");
    }

}