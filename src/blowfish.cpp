#include "../include/blowfish.h"


blowfish::blowfish()
{
    //ctor
}

blowfish::~blowfish()
{
    //dtor
}

void blowfish::blowfish_init()
{
    BF_set_key(&blow_key, sizeof(raw_key), raw_key);
}

ui blowfish::decode32le(unsigned char *buf)
{
        return (ui) buf[0] | ((ui) buf[1] << 8) | ((ui) buf[2] << 16) | ((ui) buf[3] << 24);
}

ui blowfish::decode32be(unsigned char *buf)
{
        return (ui) buf[3] | ((ui) buf[2] << 8) | ((ui) buf[1] << 16) | ((ui) buf[0] << 24);
}

void blowfish::encode32le(unsigned char* buf, ui val)
{

        buf[0] = (unsigned char) val;
        buf[1] = (unsigned char) (val >> 8);
        buf[2] = (unsigned char) (val >> 16);
        buf[3] = (unsigned char) (val >> 24);
}

void blowfish::encode32be(unsigned char* buf, ui val)
{

        buf[3] = (unsigned char) val;
        buf[2] = (unsigned char) (val >> 8);
        buf[1] = (unsigned char) (val >> 16);
        buf[0] = (unsigned char) (val >> 24);
}

ui blowfish::blowfish_encrypt(unsigned char *dest, unsigned char *src, ui src_size)
{


        ui dest_size = (src_size + 7) & (~7);

        for (ui i = 0; i < dest_size; i += 8)
        {
                // Blowfish uses big endian
                encode32be(dest + i, decode32le(src + i));
                encode32be(dest + i + 4, decode32le(src + i + 4));

                BF_ecb_encrypt(
                        (dest + i),
                        (dest + i),
                        &blow_key,
                        BF_ENCRYPT
                );

                // Enforce little endian since that's
                // the endianness used by packets
                // sent to the Lineage 2 client
                encode32le(dest + i, decode32be(dest + i));
                encode32le(dest + i + 4, decode32be(dest + i + 4));
        }

        return dest_size;
}


void blowfish::blowfish_decrypt(unsigned char *dest, unsigned char *src, ui src_size)
{

        for (ui i = 0, max = (src_size + 7) & (~7); i < max; i += 8)
        {
                // Blowfish uses big endian
                encode32be(dest + i, decode32le(src + i));
                encode32be(dest + i + 4, decode32le(src + i + 4));

                BF_ecb_encrypt(
                        (dest + i),
                        (dest + i),
                        &blow_key,
                        BF_DECRYPT
                );

                // Turn endianness back to the host machine
                encode32le(dest + i, decode32be(dest + i));
                encode32le(dest + i + 4, decode32be(dest + i + 4));
        }
}
void *blowfish::get_bf_key(unsigned char *key)
{
            for(int i = 0; i<16; i++)
            {
                key[i] = raw_key[i];
            }
}
