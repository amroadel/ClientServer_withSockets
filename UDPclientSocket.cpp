#include "UDPclientSocket.h"

UDPClientSocket::UDPClientSocket () {
    server = {0};
    sock = 0;
    myPort = 0;
    peerPort = 0;
    myAddr = {0};
    peerAddr = {0};
    hostName = new char[256];
     
}

UDPClientSocket::~UDPClientSocket () {
    delete [] hostName;
}

int UDPClientSocket::writeToSocket (char * buffer, int maxBytes) {
    return sendto(sock, buffer, maxBytes, 0, 
	        (struct sockaddr *) &peerAddr, sizeof(peerAddr));
}
int UDPClientSocket::readFromSocket (char * buffer, int maxBytes) {
    socklen_t clientlen = sizeof(peerAddr);
    return recvfrom(sock, buffer, maxBytes, 0, 
	        (struct sockaddr *) &peerAddr, &clientlen);
}

bool UDPClientSocket::initialize(char *_hostName, int _peerPort) {

    /* Creat the socket*/
    strcpy(hostName, _hostName);
    peerPort = _peerPort; 
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Problem creating client socket\n"); 
        return false; 
    }
    server = gethostbyname(hostName); 
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostName);
        return false;
    }
    /* build the server's Internet address */
    bzero(&peerAddr, sizeof(peerAddr));
    peerAddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
        (char *)&peerAddr.sin_addr.s_addr, server->h_length);
    
    peerAddr.sin_port = htons(peerPort);
    printf("Client socket initialized!\n");
    return true;
}