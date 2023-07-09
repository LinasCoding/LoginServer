#include "utility.h"

utility::utility()
{
    //ctor
}

utility::~utility()
{
    //dtor
}

void *utility::blowfish_encryption(unsigned char *buffer,short buff_len)
{
    blowfish_init();
    blowfish_encrypt(buffer+2,buffer+2,buff_len-2);
}
void *utility::blowfish_decryption(unsigned char *buffer,short buff_len)
{
    blowfish_init();
    blowfish_decrypt(buffer+2,buffer+2,buff_len-2);
}

void *utility::rsa_decryption(unsigned char *buffer, RSA *rsa_key)
{
    RSA_private_decrypt(128,buffer+3,buffer+3,rsa_key,RSA_NO_PADDING);
}

void *utility::rsa_encryption(unsigned char *buffer, RSA *rsa_key)
{
    RSA_public_encrypt(128,buffer+3,buffer+3,rsa_key,RSA_NO_PADDING);
}

void *utility::keys_generator(unsigned char *key)
{

    rsa_init();
    unsigned char temp_buffer[128] = {0};
    rsa_modulus(temp_buffer);
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

void utility::checksum_gen(unsigned char *ch_sum, unsigned char *buffer, int buff_len)
{
    unsigned int temp = 0;
    int offset = 24;
    for(int i = 2; i<buff_len-2;i+=4)
    {
        temp ^= (unsigned int)(buffer[i]<<24)
                |(unsigned int)(buffer[i+1]<<16)
                |(unsigned int)(buffer[i+2]<<8)
                |(unsigned int)(buffer[i+3]);
    }
    for(int i = 0; i<4; i++)
    {
        ch_sum[i] |= (unsigned char)((temp)>>offset);
        offset-=8;
    }


}


void utility::print_packet(unsigned char *raw, int len) {

int i, c = 0;

for(i=0;i<54;i++) printf("_");

for(i=0;i<len;i++) {

if((c % 0x10)==0) printf("\n0x%.2x | ", c);

printf("%.2x ",raw[i] & 0xFF);

c++;

}
printf("\n\n");
}

void utility::content_copy(unsigned char *dest, unsigned char *src, int source_len)
{
    for(int i = 0;i<source_len; i++)
    {
        dest[i] = src[i];
    }

}

void utility::get_session(unsigned char *session_ID, int session_len)
{

        for(int i = 0; i<4;i++)
        {
            session_info[i] = session_ID[i];
        }
        print_packet(session_info,4);


}

bool utility::check_data(unsigned char *recv_packet,unsigned char *made_packet,int packet_size)
{

    int result = 0;
    for(int i = 0; i<packet_size;i++)
    {
        result += recv_packet[i] ^ made_packet[i];

    }
    if(result==0)
         {
             return true;

         }
         else
         {
             std::cout << "Corrupted packet's data.\n";
             return false;
         }
    return true;


}

bool utility::check_len(short offset_len,short buff_len)
{
    if((offset_len^buff_len) == 0)
    {
        return true;
    }
    else
    {
        std::cout << "Wrong received packet's length.\n";
        return false;
    }
    return true;
}
