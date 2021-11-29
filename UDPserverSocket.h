#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H
class UDPServerSocket
{
    private:
        int sock;
        sockaddr_in myAddr;
        sockaddr_in peerAddr;
        int myPort;
        int peerPort;
        char *hostName;
    public:
        UDPServerSocket();
        ~UDPServerSocket();
        bool initialize (int _myPort);
        int readFromSocket (char * buffer, int maxBytes); 
        int writeToSocket (char * buffer, int maxBytes);
};
#endif // UDPSERVERSOCKET_H