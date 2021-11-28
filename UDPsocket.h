#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef UDPSOCKET_H
#define UDPSOCKET_H
class UDPSocket
{
protected:
    int sock;
    sockaddr_in myAddr;
    sockaddr_in peerAddr;
    char * myAddress;
    char * peerAddress;
    int myPort;
    int peerPort;
    bool enabled;
    char *hostName;
public: 
    UDPSocket ();
    ~UDPSocket ();
    bool initialize(char * _Addr, int _Port);
    int writeToSocket (char * buffer, int maxBytes);
    int readFromSocket (char * buffer, int maxBytes);
    int getMyPort ();
    int getPeerPort ();
    char* getHostName();
};
#endif // UDPSOCKET_H 