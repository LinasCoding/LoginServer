#ifndef SERVER_PACKETS_H
#define SERVER_PACKETS_H

#include "../lib.h"


class Server_packets : public utility
{
public:
    types types;

    public:
        Server_packets();
        virtual ~Server_packets();


     private:

        struct
        {
            unsigned char ses_ID[4] = {0};
            unsigned char ses_key1[4] = {0};
            unsigned char ses_key2[4] = {0};
        }ses_type;


        struct
        {
            unsigned char packet_size[2] = {0xba,0x00};
            unsigned char packet_type = 0x00;
            unsigned char sessionID[4] = {0};
            unsigned char protocol[4] = {0x21,0xc6,0x00,0x00};
            unsigned char rsa_module[128] = {0};
            unsigned char trash[16] = {0x4e,0x95,0xdd,0x29,
                              0xfc,0x9c,0xc3,0x77,
                              0x20,0xb6,0xad,0x97,
                              0xf7,0xe0,0xbd,0x07};
            unsigned char blowfish_static[16] = {0};
            unsigned char terninating_null = 0x00;
            unsigned char checksum[4] = {0};
            unsigned char trash1[2] = {0x69,0xCB};
            unsigned char xor_key[4] = {0};
            unsigned char padding[4] = {0};
        }init_packet;

        struct
        {
            unsigned char packet_size[2] = {0x12,0x00};
            unsigned char packet_type = 0x0b;
            unsigned char gg_response[4] = {0x0b,0x0b,0x0b,0x0b};
            unsigned char mask[4] = {0};
            unsigned char check_sum[4] = {0};
            unsigned char pad[3] = {0};
        }ggauth_packet;

        struct
        {
            unsigned char packet_size[2] = {0x2a,0x00};
            unsigned char packet_type = 0x03;
            unsigned char session_key_first[4] = {0};
            unsigned char session_key_second[4] = {0};
            unsigned char pad[15] = {0};
            unsigned char check_sum[4] = {0};
            unsigned char pad1[12] = {0};
        }login_ok_packet;

        struct
        {
            unsigned char packet_size[2] = {0x22,0x00};
            unsigned char packet_type = 0x04;
            unsigned char number_of_servers = 0x01;
            unsigned char server_number = 0x02;
            unsigned char server_id = 0x01;
            unsigned char gameserver_ip[4] = {0};
            unsigned char gameserver_port[4] = {0};
            unsigned char age_limit = 0xF0;
            unsigned char is_pvp = 0x00;
            unsigned char online_ppl[2] = {0};
            unsigned char max_players[2] = {0};
            unsigned char gameserver_status = 0x01;
            unsigned char server_status[4] = {0x00,0x00,0x00,0x00};
            unsigned char brac_before_name = 0x00;
            unsigned char pad[3] = {0x00,0x00,0x00};
            unsigned char check_sum[4] = {0};
            unsigned char pad1[2] = {0};
        }serverlist_packet;

        struct
        {
            unsigned char packet_size[2] = {0x12,0x00};
            unsigned char packet_type = 0x07;
            unsigned char session_key2_first[4] = {0};
            unsigned char session_key2_second[4] = {0};
            unsigned char unclear_data[4] = {0x01,0x00,0x00,0x00};
            unsigned char pad[3] = {0x00,0x00,0x00};
            unsigned char check_sum[4] = {0};
            unsigned char pad1[4] = {0x00,0x00,0x00,0x00};
        }play_ok_packet;

    public:
        unsigned char *init();
        unsigned char *gg_auth();
        unsigned char *login_ok();
        unsigned char *login_fail();
        unsigned char *server_list();
        unsigned char *play_ok();

        void xoring_data(unsigned char *raw_bytes,int packet_size, unsigned char *xor_key);

        unsigned char *get_session_info(int i);
        RSA *get_key;

};



#endif // SERVER_PACKETS_H
