#include "UDPsocket.h"

UDPSocket::UDPSocket() {
    sock = 0;
    myPort = 0;
    peerPort = 0;
    myAddr = {0};
    peerAddr = {0};
    hostName = new char[256]; 
    // gethostname(hostName, sizeof(hostName));
}

UDPSocket::~UDPSocket () {
    delete [] hostName;
}
bool UDPSocket::initialize (char * _myAddr, int _myPort) {
    return false;
}

int UDPSocket::writeToSocket (char * buffer, int maxBytes) {
    return sendto(sock, buffer, maxBytes, 0, 
	        (struct sockaddr *) &peerAddr, sizeof(peerAddr));
}
int UDPSocket::readFromSocket (char * buffer, int maxBytes) {
    socklen_t clientlen = sizeof(peerAddr);
    return recvfrom(sock, buffer, maxBytes, 0, 
	        (struct sockaddr *) &peerAddr, &clientlen);
}
int UDPSocket::getMyPort () {
    return myPort;
}
int UDPSocket::getPeerPort () {
    return peerPort;
}
char* UDPSocket::getHostName() {
    return hostName;
}