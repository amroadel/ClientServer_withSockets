#include "UDPclientSocket.h"
#ifndef CLIENT_H
#define CLIENT_H
#define BUFSIZE 1024
class client
{
    private:
        UDPClientSocket * udpSocket;
        char buffer[BUFSIZE]; 
    public:
        client(char * _hostname, int _port);
        void execute(); 
        ~client();
};
#endif // CLIENT_H