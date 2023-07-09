#include "l2_sockets.h"


l2_sockets::l2_sockets()
{
    wsaVersionRequested();
    serverInfo(IP_ADDRESS,PORT_NUMBER);
    socketBind();
    listening();
    acception();
}

l2_sockets::~l2_sockets()
{
    close_socket();
}

void l2_sockets::clients_id(SOCKET *id)
{
    int i = 1;
    if(i<100)
    {
        id[i];
        std::cout << "Clients ID: "<< i <<std::endl;
        i++;
    }
}

void *l2_sockets::wsaVersionRequested()
{
    // Using MAKEWORD macro, Winsock version request 2.2

       wsaVersion = MAKEWORD(2, 2);
       wsaErr = WSAStartup(wsaVersion, &wsaData);

       if (wsaErr != 0)
       {
           std::cout<<"Server: The Winsock dll not found!\n";
       }
       else
       {
           std::cout << "Server: The Winsock dll found!\n";
           std::cout << "Server: The status: "<<wsaData.szSystemStatus<< std::endl;
       }
}

void *l2_sockets::serverInfo(const char *ip, int port)
{

    serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET)
       {
           std::cout << "Server: Error at socket(): " << WSAGetLastError() <<std::endl;
           WSACleanup();
           return 0;
       }
    else
       {
          std::cout << "Server: socket() is OK!\n";
       }

       server.sin_family = AF_INET;
       server.sin_addr.s_addr = inet_addr(ip);
       server.sin_port = htons(port);
       std::cout << inet_ntoa(server.sin_addr)<< std::endl;

}

void *l2_sockets::socketBind()
{



    if (bind(serverSocket, (SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR)
      {
        std::cout<<"Server: bind() failed: "<<WSAGetLastError()<<std::endl;
         closesocket(serverSocket);
         return 0;
      }
    else
      {
        std::cout<<"Server: bind() is OK!\n";
      }

}

void *l2_sockets::listening()
{

        list_array = listen(serverSocket, 10);

    if ( list_array == SOCKET_ERROR)
      {
         std::cout <<"Server: listen(): Error listening on socket "<<WSAGetLastError() <<std::endl;

      }
    else
      {
         std::cout<<"Server: listen() is OK, waiting for connections...\n";

      }

       std::cout<<"Server: Waiting for a client to connect...\n";


}

void *l2_sockets::acception()
{
    std::thread thrr[MAX_CONN];
    int clientsize = sizeof(client);

     for(int i = 0;i<MAX_CONN;i++)
     {
        accepted[i] = accept(serverSocket, (SOCKADDR*)&client, &clientsize);
        thrr[i] = std::thread(&l2_sockets::ready_to_send,this,accepted[i]);
        std::cout << "Number "<<i+1<<" thread running.\n";
        printf("Server: Client Connected with address %s and port %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));
     }

     for(int i = 0; i<MAX_CONN;i++)
     {
         if(thrr[i].joinable())
         {
             thrr[i].join();
             std::cout<<"Joined.\n";
         }
     }
}


int *l2_sockets::sendPacket(unsigned char* packet, int packet_lenght,int socket)
{

   bytesSent = send(socket,(char*)packet,packet_lenght,0);

   if(bytesSent == SOCKET_ERROR)
   {
       std::cout<<"Server socket error while sending... "<<WSAGetLastError()<<std::endl;
       closesocket(bytesSent);
   }
   else
   {
       std::cout<< packet<< std::endl;
       std::cout<<"Server: send() is OK.\n";
       std::cout<<"Server: Bytes Sent: "<<bytesSent<<std::endl;
   }
   return 0;
}

int *l2_sockets::recvPacket(unsigned char *packet, int packet_lenght,int socket)
{

   bytesRecv = recv(socket,(char*)packet,packet_lenght,0);

   if(bytesRecv == SOCKET_ERROR)
   {
       std::cout<<"Server socket error while reveiving... "<<WSAGetLastError()<<std::endl;
       closesocket(bytesSent);
   }
   else
   {
       std::cout << packet << std::endl;
       std::cout<<"Server: recv() is OK.\n";
       std::cout<<"Server: Bytes Received: "<<bytesRecv<<std::endl;
   }
   return 0;
}



void *l2_sockets::ready_to_send(int sock)
{

    Server_packets sp;
    Client_packets cp;

    unsigned char pss[42] = {0};
    unsigned char buffer[178] = {0};
    unsigned char buff[34] = {0};
    unsigned char buff1[34] = {0};
    unsigned char buff2[128] = {0};

    sendPacket(sp.init(),186,sock);


    recvPacket(pss,42,sock);
    cp.request_ggauth(pss,42,sp.get_session_info(0));

    sendPacket(sp.gg_auth(),18,sock);

    recvPacket(buffer,178,sock);
    cp.request_auth_login(buffer,178,sp.get_key);

    sendPacket(sp.login_ok(),42,sock);

    recvPacket(buff,34,sock);
    cp.request_server_list(buff,34,sp.get_session_info(1),sp.get_session_info(2));

    sendPacket(sp.server_list(),34,sock);

    recvPacket(buff1,34,sock);
    cp.request_server_login(buff1,34,sp.get_session_info(1),sp.get_session_info(2));

    sendPacket(sp.play_ok(),42,sock);

}


void l2_sockets::close_socket()
{
    shutdown(serverSocket,SD_SEND);
    closesocket(serverSocket);
    std::cout << "Socket closed.\n";
}
