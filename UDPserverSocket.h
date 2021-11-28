#include "UDPsocket.h"

#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H
class UDPServerSocket : public UDPSocket
{
    public:
        UDPServerSocket();
        bool initialize (int _myPort);
        int readFromSocket (char * buffer, int maxBytes); 
        ~UDPServerSocket();
};
#endif // UDPSERVERSOCKET_H