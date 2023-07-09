#include "Server_packets.h"

Server_packets::Server_packets()
{

}

Server_packets::~Server_packets()
{

}

void Server_packets::xoring_data(unsigned char *raw_bytes,int packet_size, unsigned char *xor_key)
{

    unsigned int temp_xor_key; // O_o generate random XOR "key"
	int xor_offset = 6; //2; // should we XOR login session id also?
	while( xor_offset < packet_size )
	{
		// read current dword
		unsigned int xoring_dword =
			(unsigned int)raw_bytes[xor_offset] |
			((unsigned int)raw_bytes[xor_offset+1]) << 8 |
			((unsigned int)raw_bytes[xor_offset+2]) << 16 |
			((unsigned int)raw_bytes[xor_offset+3]) << 24;
		temp_xor_key += xoring_dword; // increase xor key by xoring dword before XOR
		xoring_dword ^= temp_xor_key; // XOR
		// decodeXOR() first XORs, then substracts :) and it goes from end of packet to beginning
		// update dword inside packet
		raw_bytes[xor_offset]   = (unsigned char)(xoring_dword & 0xFF);
		raw_bytes[xor_offset+1] = (unsigned char)(xoring_dword >> 8 & 0x00FF);
		raw_bytes[xor_offset+2] = (unsigned char)(xoring_dword >> 16 & 0x0000FF);
		raw_bytes[xor_offset+3] = (unsigned char)(xoring_dword >> 24 & 0x000000FF);
		// move to next dword
		xor_offset += 4;
		xor_key = (unsigned char*)&temp_xor_key;
	}

};

unsigned char *Server_packets::init()
{

    int buff_len = 186;
    unsigned char *buffer;
    //reference to struct memory
    buffer = &(init_packet.packet_size[0]);
   keys_generator(init_packet.sessionID);

   content_copy(ses_type.ses_ID,init_packet.sessionID,4);
   print_packet(init_packet.sessionID,4);

   rsa_modulus(init_packet.rsa_module);
   get_key = key;

   keys_generator(init_packet.padding);
   get_bf_key(init_packet.blowfish_static);

   checksum_gen(buffer+172,buffer,buff_len-10);
   print_packet(buffer,186);
   xoring_data(buffer,buff_len,init_packet.xor_key);
   print_packet(buffer,186);
   this->blowfish_encryption(buffer,buff_len);

   return buffer;
}

unsigned char *Server_packets::gg_auth()
{
    unsigned char *buffer;
    int buff_len = 18;
    //reference to struct memory
    buffer = &(ggauth_packet.packet_size[0]);
    keys_generator(ggauth_packet.mask);
    checksum_gen(buffer+14,buffer,buff_len);
    this->blowfish_encryption(buffer,buff_len);

    return buffer;
}

unsigned char *Server_packets::login_ok()
{
    unsigned char *buffer;
    int buff_len = 42;
    //reference to struct memory
    buffer = &(login_ok_packet.packet_size[0]);
    keys_generator(login_ok_packet.session_key_first);
    keys_generator(login_ok_packet.session_key_second);
    content_copy(ses_type.ses_key1,login_ok_packet.session_key_first,4);
    content_copy(ses_type.ses_key2,login_ok_packet.session_key_second,4);

    checksum_gen(login_ok_packet.check_sum,buffer,buff_len-12);
    print_packet(buffer,42);
    this->blowfish_encryption(buffer,buff_len);

    return buffer;
}

unsigned char *Server_packets::login_fail()
{
    //not started yet
}

unsigned char *Server_packets::server_list()
{
    unsigned char *buffer;
    int buff_len = 34;
    //reference to struct memory
    buffer = &(serverlist_packet.packet_size[0]);
    types.write_long(inet_addr("127.0.0.1"),serverlist_packet.gameserver_ip);
    types.write_short(7777,serverlist_packet.gameserver_port);
    types.write_short(1,serverlist_packet.online_ppl);
    types.write_short(1000,serverlist_packet.max_players);

    print_packet(buffer,34);

    checksum_gen(serverlist_packet.check_sum,buffer,buff_len-10);
    this->blowfish_encryption(buffer,buff_len);

    return buffer;
}

unsigned char *Server_packets::play_ok()
{
    unsigned char *buffer;
    int buff_len = 42;
    //reference to struct memory
    buffer = &(play_ok_packet.packet_size[0]);
    keys_generator(play_ok_packet.session_key2_first);
    keys_generator(play_ok_packet.session_key2_second);

    checksum_gen(play_ok_packet.check_sum,buffer,buff_len-12);
    this->blowfish_encryption(buffer,buff_len);

    return buffer;
}

unsigned char *Server_packets::get_session_info(int i)
{
    switch(i)
    {
    case 0:
       return ses_type.ses_ID;
       break;

    case 1:
        return ses_type.ses_key1;
        break;

    case 2:
        return ses_type.ses_key2;
        break;

    default:
        std::cout << "No such a session key.\n";
        break;
    }
}
