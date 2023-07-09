#ifndef UTILITY_H
#define UTILITY_H
#include "../lib.h"

class utility : public blowfish, public rsa, public types
{
    public:
        utility();
        virtual ~utility();
        void *blowfish_encryption(unsigned char *buffer,short buff_len);
        void *blowfish_decryption(unsigned char *buffer,short buff_len);
        void *rsa_decryption(unsigned char *buffer, RSA *rsa_key);
        void *rsa_encryption(unsigned char *buffer, RSA *rsa_key);
        void *keys_generator(unsigned char *key);
        static void checksum_gen(unsigned char *ch_sum, unsigned char *buffer, int buff_len);
        void print_packet(unsigned char *raw, int len);
        void content_copy(unsigned char *dest, unsigned char *src, int source_len);
        void get_session(unsigned char *session_ID, int session_len);
        bool check_data(unsigned char *recv_packet,unsigned char *made_packet,int packet_size);

        bool check_len(short offset_len,short buff_len);

        unsigned char session_info[4];


    private:
};

#endif // UTILITY_H
