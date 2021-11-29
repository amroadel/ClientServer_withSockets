#include "client.h"

client::client(char * _hostname, int _port) {
    udpSocket = new UDPClientSocket; 
    if(!udpSocket->initialize(_hostname, _port)) {
        exit(EXIT_FAILURE); 
    } 
}

client::~client() {
    delete udpSocket; 
}

void client::execute() {
    bzero(buffer, BUFSIZE);
    printf("Please enter msg: ");
    fgets(buffer, BUFSIZE, stdin);

    if (udpSocket->writeToSocket(buffer, BUFSIZE) < 0) {
        perror("Error sending from client\n"); 
        exit(EXIT_FAILURE);
    }

    if (udpSocket->readFromSocket(buffer, BUFSIZE) < 0) {
        perror("Error receiving from server\n"); 
        exit(EXIT_FAILURE);
    }
    printf("Echo from server: %s", buffer);
}