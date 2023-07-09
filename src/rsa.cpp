#include "../include/rsa.h"

rsa::rsa()
{
    rsa_init();
}

rsa::~rsa()
{
    rsa_free();
}

void rsa::rsa_init()
{
        this->e = BN_new();
        this->key = RSA_new();

        BN_dec2bn(&e, "65537");
        RSA_generate_key_ex(this->key,1024, this->e, NULL);

}

void rsa::rsa_free()
{
        BN_free(this->e);
        RSA_free(this->key);
}

int rsa::rsa_size()
{
        return RSA_size(this->key);
}

void rsa::rsa_scramble_modulo(unsigned char *n)
{
        unsigned char temp = 0;
        int i = 0;

        for (i = 0; i < 4; i ++)
        {
                temp = n[0x00 + i];
                n[0x00 + i] = n[0x4d + i];
                n[0x4d + i] = temp;
        };

        // step 2 xor first 0x40 bytes with last 0x40 bytes
        for (i = 0; i < 0x40; i++)
        {
                n[i] = (unsigned char) (n[i] ^ n[0x40 + i]);
        };

        // step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
        for (i = 0; i < 4; i ++)
        {
                n[0x0d + i] = (unsigned char) (n[0x0d + i] ^ n[0x34 + i]);
        };

        // step 4 xor last 0x40 bytes with first 0x40 bytes
        for (i = 0; i < 0x40; i ++)
        {
                n[0x40 + i] = (unsigned char) (n[0x40 + i] ^ n[i]);
        };
}

void rsa::unscrambleMod(unsigned char *n)
{
      typedef unsigned char byte;
      int i;

      // step 4 xor last 0x40 bytes with first 0x40 bytes
      for( i=0; i<0x40; i++ ) {
            n[0x40 + i] = (byte)(n[0x40 + i] ^ n[i]);
      };

      // step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
      for( i=0; i<4; i++ ) {
            n[0x0d + i] = (byte)(n[0x0d + i] ^ n[0x34 + i]);
      };

      // step 2 xor first 0x40 bytes with last 0x40 bytes
      for( i=0; i<0x40; i++ ) {
            n[i] = (byte)(n[i] ^ n[0x40 + i]);
      };

      for( i=0; i<4; i++ ) {
            byte temp = n[0x00 + i];
            n[0x00 + i] = n[0x4d + i];
            n[0x4d + i] = temp;
      };
};

void rsa::rsa_modulus(unsigned char* dest)
{

        const BIGNUM *n = NULL;

        RSA_get0_key(this->key, &n, NULL, NULL);
        BN_bn2bin(n,dest);
        rsa_scramble_modulo(dest);
}

int rsa::rsa_decrypt( unsigned char* src, unsigned char* dest)
{


        return RSA_private_decrypt(
                rsa_size(),
                src,
                dest,
                key,
                RSA_NO_PADDING
        );
}

void rsa::print_packet(unsigned char *raw, int len)
{

int i, c = 0;

for(i=0;i<54;i++) printf("_");

for(i=0;i<len;i++) {

if((c % 0x10)==0) printf("\n0x%.2x | ", c);

printf("%.2x ",raw[i] & 0xFF);

c++;

}
printf("\n\n");
}


