#ifndef L2_SOCKETS_H
#define L2_SOCKETS_H

#include "../lib.h"

#include "Server_packets.h"
#include "Client_packets.h"

#define MAX_CONN 2 //connections and threads maximum number
#define PORT_NUMBER 2106 //port number
#define IP_ADDRESS "127.0.0.1" //IP address

class l2_sockets
{
    public:
        l2_sockets();
        virtual ~l2_sockets();
        void *wsaVersionRequested();

        void *serverInfo(const char *ip, int port);
        void *socketBind();
        void *listening();
        void *acception();
        void clients_id(SOCKET *id);

        int *sendPacket(unsigned char *packet,int packet_lenght,int socket);
        int *recvPacket(unsigned char *packet, int packet_lenght,int socket);

        void *ready_to_send(int sock);

        void close_socket();

    private:

        WORD wsaVersion;
        WSADATA wsaData;
        int wsaErr;
        SOCKET serverSocket = SOCKET_ERROR;

        int accepted[MAX_CONN];

        int list_array;

        sockaddr_in server;
        sockaddr_in client;

        int bytesSent = SOCKET_ERROR;
        int bytesRecv = SOCKET_ERROR;






};

#endif // L2_SOCKETS_H
