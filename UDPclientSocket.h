#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef UDPCLIENTSOCKET_H
#define UDPCLIENTSOCKET_H
class UDPClientSocket
{
    private:
        struct hostent *server;
        int sock;
        sockaddr_in myAddr;
        sockaddr_in peerAddr;
        int myPort;
        int peerPort;
        char *hostName;
    public:
        UDPClientSocket ();
        ~UDPClientSocket ();
        bool initialize(char *_hostName, int _peerPort);
        int writeToSocket (char * buffer, int maxBytes);
        int readFromSocket (char * buffer, int maxBytes);
};
#endif // UDPCLIENTSOCKET_H