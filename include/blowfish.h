#ifndef BLOWFISH_H
#define BLOWFISH_H

#include "openssl/blowfish.h"

typedef uint32_t ui;

class blowfish
{
    public:
        blowfish();
        virtual ~blowfish();


        void blowfish_init();
        ui decode32le(unsigned char *buf);
        ui decode32be(unsigned char *buf);
        void encode32le(unsigned char* buf, ui val);
        void encode32be(unsigned char* buf, ui val);
        ui blowfish_encrypt(unsigned char *dest, unsigned char *src, ui src_size);
        void blowfish_decrypt(unsigned char *dest, unsigned char *src, ui src_size);
        void *get_bf_key(unsigned char *key);



   private:
       BF_KEY blow_key;
       unsigned char raw_key[16] = {0x6B, 0x60, 0xCB, 0x5B, 0x82, 0xCE, 0x90, 0xB1, 0xCC, 0x2B, 0x6C, 0x55, 0x6C, 0x6C, 0x6C, 0x6C};


};

#endif // BLOWFISH_H
