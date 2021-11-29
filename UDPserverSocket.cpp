#include "UDPserverSocket.h"

UDPServerSocket::UDPServerSocket() {
    sock = 0;
    myPort = 0;
    peerPort = 0;
    myAddr = {0};
    peerAddr = {0};
    hostName = new char[256];
}

UDPServerSocket::~UDPServerSocket() {
    delete [] hostName;
}

bool UDPServerSocket::initialize(int _myPort) {
    myPort = _myPort; 
    /* socket: create the parent socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sock < 0) {
        perror("Problem creating server socket\n"); 
        return false;
    }

    /* Eliminates "ERROR on binding: Address already in use" error. */
    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
	        (const void *)&optval , sizeof(int));
    
    
    /* Set the server's Internet address */
    bzero(&myAddr, sizeof(myAddr));
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myAddr.sin_port = htons((unsigned short)myPort);

    /* bind: associate the parent socket with a port */
    if (bind(sock, (struct sockaddr *) &myAddr, sizeof(myAddr)) < 0) {
        perror("ERROR on server binding");
        return false;
    }

    return true;

}

int UDPServerSocket::writeToSocket (char * buffer, int maxBytes) {
    return sendto(sock, buffer, maxBytes, 0, 
	        (struct sockaddr *) &peerAddr, sizeof(peerAddr));
}

int UDPServerSocket::readFromSocket (char * buffer, int maxBytes) {
    socklen_t clientlen = sizeof(peerAddr);
    int n;
    struct hostent *hostp;
    char *hostaddrp; /* dotted decimal host addr string */
    n = recvfrom(sock, buffer, maxBytes, 0, 
	    (struct sockaddr *) &peerAddr, &clientlen);
    
    /* gethostbyaddr: determine who sent the datagram */
    hostp = gethostbyaddr((const char *)&peerAddr.sin_addr.s_addr, 
			  sizeof(peerAddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      perror("ERROR on gethostbyaddr");

    hostaddrp = inet_ntoa(peerAddr.sin_addr);
    if (hostaddrp == NULL)
      perror("ERROR on inet_ntoa\n");

    printf("server received datagram from %s (%s)\n", 
	   hostp->h_name, hostaddrp);
    printf("server received %d/%d bytes: %s\n", strlen(buffer), n, buffer);

    return n; 
}