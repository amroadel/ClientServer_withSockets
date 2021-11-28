#include "client.h"

client::client(char * _hostname, int _port) {
    if(!udpSocket->initialize(_hostname, _port)) {
        exit(0); 
    }
}

void client::execute() {
    bzero(buffer, BUFSIZE);
    printf("Please enter msg: ");
    fgets(buffer, BUFSIZE, stdin);

    if (udpSocket->writeToSocket(buffer, BUFSIZE) < 0) {
        perror("Error sending from client\n"); 
        exit(0);
    }

    if (udpSocket->readFromSocket(buffer, BUFSIZE) < 0) {
        perror("Error receiving from server\n"); 
        exit(0);
    }
    printf("Echo from server: %s", buffer);
}