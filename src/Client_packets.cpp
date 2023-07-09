#include "Client_packets.h"

Client_packets::Client_packets()
{
    //ctor
}

Client_packets::~Client_packets()
{
    //dtor
}

bool Client_packets::request_ggauth(unsigned char *buffer,short buff_len,unsigned char *session_ID)
{

    unsigned char *offset;
    short offset_len = 42;
    blowfish_decryption(buffer,buff_len);
    offset = &(request_ggauth_packet.packet_size[0]);
    content_copy(request_ggauth_packet.session_ID,session_ID,4);

    checksum_gen(request_ggauth_packet.check_sum,offset,offset_len-12);

    print_packet(buffer,buff_len);
    print_packet(offset,offset_len);

    check_data(buffer,offset,offset_len);

    return true;

}
bool Client_packets::request_auth_login(unsigned char *buffer,short buff_len,RSA *rsa_key)
{
    unsigned char *offset;
    short offset_len = 178;
    blowfish_decryption(buffer,buff_len);
    utility::rsa_decryption(buffer,rsa_key);
    check_len(offset_len,buff_len);

    offset = &(request_auth_login_packet.packet_size[0]);
    str_to_hex(request_auth_login_packet.login_id,"labas");
    str_to_hex(request_auth_login_packet.password,"krabas");

    check_data(buffer,offset,offset_len);

    utility::rsa_encryption(offset,rsa_key);
    checksum_gen(request_auth_login_packet.checksum,offset,offset_len-12);

    print_packet(buffer,buff_len);
    print_packet(offset,offset_len);

    return true;

}
bool Client_packets::request_server_list(unsigned char *buffer,short buff_len,unsigned char *session_key1_first,unsigned char *session_key1_second)
{
    unsigned char *offset;
    short offset_len = 34;
    blowfish_decryption(buffer,buff_len);
    check_len(offset_len,buff_len);

    offset = &(request_server_list_packet.packet_size[0]);
    content_copy(request_server_list_packet.session_key_first,session_key1_first,4);
    content_copy(request_server_list_packet.session_key_second,session_key1_second,4);

    checksum_gen(request_server_list_packet.checksum,offset,offset_len-12);

    check_data(offset,buffer,buff_len);

    print_packet(buffer,buff_len);
    print_packet(offset,offset_len);

    return true;
}
bool Client_packets::request_server_login(unsigned char *buffer,short buff_len,unsigned char *session_key1_first,unsigned char *session_key1_second)
{
    unsigned char *offset;
    short offset_len = 34;
    blowfish_decryption(buffer,buff_len);
    check_len(offset_len,buff_len);

    offset = &(request_server_login_packet.packet_size[0]);
    content_copy(request_server_login_packet.session_key_first,session_key1_first,4);
    content_copy(request_server_login_packet.session_key_second,session_key1_second,4);

    checksum_gen(request_server_login_packet.checksum,offset,offset_len-12);

    check_data(offset,buffer,buff_len);

    print_packet(buffer,buff_len);
    print_packet(offset,offset_len);

    return true;
}
