#include "UDPsocket.h"

#ifndef UDPCLIENTSOCKET_H
#define UDPCLIENTSOCKET_H
class UDPClientSocket : public UDPSocket
{
    private:
        struct hostent *server;
    public:
        UDPClientSocket ();
        bool initialize(char *_hostName, int _peerPort);
        ~UDPClientSocket ( );
};
#endif // UDPCLIENTSOCKET_H