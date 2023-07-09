#include "types.h"

types::types()
{
    //ctor
}

types::~types()
{
    //dtor
}

char types::read_char(char *packet)
{
    return *packet;
}

 unsigned short types::read_short(unsigned char *buffer, unsigned int offset)
{
       return (unsigned short)((buffer[offset+1]<<8) | (buffer[offset]));

}

int types::read_int(int *packet)
{
    return *packet;
}

double types::read_double(double *packet)
{
    return *packet;
}

void types::write_char(int8_t opcodes, unsigned char *buffer)
{
    for(int i = 0; i<1; i++)
    {
        buffer[i] = opcodes;
    }
}

void types::write_short(int16_t opcodes, unsigned char *buffer)
{
        int offset = 0;
        for(int i = 0; i < 2; i++)
        {
             buffer[i] = (unsigned char)((opcodes>>offset)&0xFF);
             offset+=8;
        }
}

void types::write_int(int32_t opcodes, unsigned char *buffer)
{
        int offset = 0;
        for(int i = 0; i < 4; i++)
        {
             buffer[i] = (unsigned char)((opcodes>>offset)&0xFF);
             offset+=8;
        }
}

void types::write_long(int64_t opcodes, unsigned char *buffer)
{
        int offset = 0;
        for(int i = 0; i < 8; i++)
        {
             buffer[i] = (unsigned char)((opcodes>>offset)&0xFF);
             offset+=8;
        }
}

void types::write_double(double opcodes, unsigned char *buffer)
{

    unsigned char *opcodeptr = (unsigned char*)&opcodes;

        for(int i = 0; i < 8; i++)
        {
             buffer[i] = opcodeptr[i];
        }

}

void types::write_unicode(char *utf8,unsigned char *buffer,int buffer_size)
{
    int j = 0;
    int unicode_size = buffer_size*2;
    for(int i = 0;i<unicode_size;i+=2)
    {
        utf8[i] = (char)buffer[j++];
        utf8[i+1] = utf8[i+1]&0x00;
    }
       utf8[unicode_size] = utf8[unicode_size+1]&0x00;
       utf8[unicode_size+1] = utf8[unicode_size+2]&0x00;
}

void types::write_uint(uint32_t opcodes, unsigned char *buffer)
{
        int offset = 0;
        for(int i = 0; i < 4; i++)
        {
             buffer[i] = (unsigned char)((opcodes>>offset)&0xFF);
             offset+=8;
        }
}

void *types::str_to_hex(unsigned char *dest,std::string str)
{
    for(int i = 0; i<str.length();i++)
    {
        str.copy((char*)dest+i,1,i);
    }

}
