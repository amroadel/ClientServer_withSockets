#include "UDPserverSocket.h"
#ifndef SERVER_H
#define SERVER_H
#define BUFSIZE 1024
class server
{
private:
UDPServerSocket * udpServerSocket;
char buffer[BUFSIZE];
// Message * getRequest();
// Message * doOperation();
// void sendReply (Message * _message);
public:
server(char * _listen_hostname, int _listen_port);
void serveRequest();
~server();
};
#endif // SERVER_H