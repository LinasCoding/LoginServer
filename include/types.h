#ifndef TYPES_H
#define TYPES_H

#include <iostream>

typedef unsigned char byte;
typedef unsigned short two_bytes;
typedef unsigned int fourth_bytes;
typedef unsigned long long eight_bytes;
typedef double double_eight_bytes;

class types
{
    public:
        types();
        virtual ~types();

        char read_char(char *packet);
        unsigned short read_short(unsigned char *buffer, unsigned int offset);
        int read_int(int *packet);
        double read_double(double *packet);
        void read_bytes(byte type_size);

        void write_char(int8_t opcodes, unsigned char *buffer);
        void write_short(int16_t opcodes, unsigned char *buffer);
        void write_int(int32_t opcodes, unsigned char *buffer);
        void write_long(int64_t opcodes, unsigned char *buffer);
        void write_double(double opcodes, unsigned char *buffer);
        void write_unicode(char *utf8,unsigned char *buffer,int buffer_size);

        void write_uint(uint32_t opcodes, unsigned char *buffer);

        void short_to_hex(unsigned char *buffer, short val);
        void int_to_hex(unsigned char *buffer, int val);

        void *str_to_hex(unsigned char *dest,std::string str);


    private:


};

#endif // TYPES_H
