#include "server.h"

server::server(char * _listen_hostname, int _listen_port) {
     
    if(!udpServerSocket->initialize(_listen_port)) {
        exit(0); 
    }
}
void server::serveRequest() {
    while(true) {

        if (udpServerSocket->readFromSocket(buffer, BUFSIZE) < 0) {
            perror("Error receiving from client\n"); 
            exit(0);
        }

        if (udpServerSocket->writeToSocket(buffer, BUFSIZE) < 0) {
            perror("Error sending from server\n"); 
            exit(0);
        }
    }
}