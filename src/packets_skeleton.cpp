#include "packets_skeleton.h"


packets_skeleton::packets_skeleton()
{
    //ctor
}

packets_skeleton::~packets_skeleton()
{
    //dtor
}

void *packets_skeleton::keys_generator(unsigned char *key)
{
    rsa rsa;
    rsa.rsa_init();
    unsigned char temp_buffer[128] = {0};
    rsa.rsa_modulus(temp_buffer);
    unsigned int temp_key = 0;
    int offset = 0;
    for(int i = 0; i<128; i+=4)
    {
        temp_key ^= (unsigned int)(temp_buffer[i])
                    |(unsigned int)(temp_buffer[i+1]<<8)
                    |(unsigned int)(temp_buffer[i+2]<<16)
                    |(unsigned int)(temp_buffer[i+3]<<24);
    }
    for(int i = 0; i<4; i++)
    {
        key[i] = 0;
        key[i] |= (unsigned char)(temp_key>>offset);
        offset+=8;
    }

}

void packets_skeleton::print_packet(unsigned char *raw, int len) {

int i, c = 0;

for(i=0;i<54;i++) printf("_");

for(i=0;i<len;i++) {

if((c % 0x10)==0) printf("\n0x%.2x | ", c);

printf("%.2x ",raw[i] & 0xFF);

c++;

}
printf("\n\n");
}

void packets_skeleton::content_copy(unsigned char *dest, unsigned char *src, int source_len)
{
    for(int i = 0;i<source_len; i++)
    {
        dest[i] = src[i];
    }

}

/*
buffer_len &packets_skeleton::login_info(byte *packet,byte *credentials)
{
        buffer_len cre_len = data_lenght(credentials);
            if(cre_len>5)
            {
                 for(int i= 0;i<cre_len;i++)
                    {
                       packet[i] = credentials[i];
                    }
                    std::cout << cre_len<< std::endl;
            }
            else
            {
                std::cout << "Your's credentials are too short!\n";
            }


            return cre_len;
}
*/
