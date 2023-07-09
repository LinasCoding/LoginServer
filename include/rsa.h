#ifndef RSA_H
#define RSA_H

#include "iostream"

#include "openssl/bn.h"
#include "openssl/rsa.h"


class rsa
{
    public:
        rsa();
        virtual ~rsa();

    public:
        void rsa_init();
        void rsa_free();
        int rsa_size();
        void rsa_scramble_modulo(unsigned char *n);
        void unscrambleMod(unsigned char *n);
        void rsa_modulus(unsigned char* dest);
        int rsa_decrypt(unsigned char* src, unsigned char* dest);
        void print_packet(unsigned char *raw, int len);

    protected:
        BIGNUM* e;
        RSA* key;



};

#endif // RSA_H
