#include "server.h"

server::server(char * _listen_hostname, int _listen_port) {
    udpServerSocket = new UDPServerSocket;
    if(!udpServerSocket->initialize(_listen_port)) {
        exit(EXIT_FAILURE); 
    }

}

server::~server(){
    delete udpServerSocket;
}
void server::serveRequest() {
    while(true) {

        if (udpServerSocket->readFromSocket(buffer, BUFSIZE) < 0) {
            perror("Error receiving from client\n"); 
            exit(EXIT_FAILURE);
        }

        if (udpServerSocket->writeToSocket(buffer, BUFSIZE) < 0) {
            perror("Error sending from server\n"); 
            exit(EXIT_FAILURE);
        }
    }
}