#include "UDPclientSocket.h"

UDPSocket::UDPSocket() {
    
}

bool UDPClientSocket::initialize(char *_hostName, int _peerPort) {

    /* Creat the socket*/
    hostName = _hostName;
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
    return true;
}