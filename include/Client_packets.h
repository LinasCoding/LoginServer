#ifndef CLIENT_PACKETS_H
#define CLIENT_PACKETS_H
#include "../lib.h"

class Client_packets : public utility
{

    public:
        Client_packets();
        virtual ~Client_packets();



         unsigned char key[4] = {0};

    private:
        struct
        {
            unsigned char packet_size[2] = {0x2a,0x00};
            unsigned char packet_type = 0x07;
            unsigned char session_ID[4] = {0};
            unsigned char random_data[19] = {0};
            unsigned char check_sum[4] = {0};
            unsigned char pad[12] = {0};
        }request_ggauth_packet;

        struct
        {
            unsigned char packet_size[2] = {0xb2,0x00};
            unsigned char packet_type = 0x00;
            unsigned char rsa_decrypt_data_begin[90] = {0};
            unsigned char rsa_decrypt_some_data[4] = {0x00,0x24,0x00,0x00};
            unsigned char login_id[14] = {0};
            unsigned char password[16] = {0};
            unsigned char rsa_decrypt_data_end[4] = {0};
            unsigned char gg_auth_response[4] = {0x0b,0x0b,0x0b,0x0b};
            unsigned char pad[16] = {0};
            unsigned char creds_marker = 0x08;
            unsigned char pad1[10] = {0};
            unsigned char checksum[4] = {0};
            unsigned char pad2[12] = {0};
        }request_auth_login_packet;

         struct
        {
            unsigned char packet_size[2] = {0x22,0x00};
            unsigned char packet_type = 0x05;
            unsigned char session_key_first[4] = {0};
            unsigned char session_key_second[4] = {0};
            unsigned char trash[4] = {0x04,0x00,0x00,0x00};
            unsigned char pad[3] = {0};
            unsigned char checksum[4] = {0};
            unsigned char pad1[12] = {0};
        }request_server_list_packet;

        struct
        {
            unsigned char packet_size[2] = {0x22,0x00};
            unsigned char packet_type = 0x02;
            unsigned char session_key_first[4] = {0};
            unsigned char session_key_second[4] = {0};
            unsigned char servers_number = 0x01;
            unsigned char pad[6] = {0};
            unsigned char checksum[4] = {0};
            unsigned char pad1[12] = {0};

        }request_server_login_packet;

    public:
        bool request_ggauth(unsigned char *buffer,short buff_len,unsigned char *session_ID);
        bool request_auth_login(unsigned char *buffer,short buff_len, RSA *rsa_key);
        bool request_server_list(unsigned char *buffer,short buff_len,unsigned char *session_key1_first,unsigned char *session_key1_second);
        bool request_server_login(unsigned char *buffer,short buff_len,unsigned char *session_key1_first,unsigned char *session_key1_second);

    public:
        unsigned char get_sessionID[4] = {0};


};

#endif // CLIENT_PACKETS_H
