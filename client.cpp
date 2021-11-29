#include "client.h"
#include "message.h"
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
    buffer[strlen(buffer) - 1 ] = '\0';

    Message m1(0, buffer, strlen(buffer), 0);

    if (udpSocket->writeToSocket(m1.marshal(), BUFSIZE) < 0) {
        perror("Error sending from client\n"); 
        exit(EXIT_FAILURE);
    }

    if (udpSocket->readFromSocket(buffer, BUFSIZE) < 0) {
        perror("Error receiving from server\n"); 
        exit(EXIT_FAILURE);
    }
    
    Message m2(buffer, strlen(buffer));
    char *buffer2 = (char*)m2.getMessage();
    printf("Echo from server: %s\n", buffer2);
}