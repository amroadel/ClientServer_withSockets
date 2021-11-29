#include "server.h"
#include "message.h"
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
    char *e; 
    while (true) {

        fgets(e, 1, stdin);
        if (strcmp(e, "q") != 0) {
            break; 
        }

        if (udpServerSocket->readFromSocket(buffer, BUFSIZE) < 0) {
            perror("Error receiving from client\n"); 
            exit(EXIT_FAILURE);
        }
        Message m1(buffer, strlen(buffer));
        char *buffer2 = (char*)m1.getMessage();
        printf("server received %d/%d bytes: %s\n", strlen(buffer), BUFSIZE, buffer2);

        Message m2(0, buffer2, strlen(buffer2), 0); 

        if (udpServerSocket->writeToSocket(m2.marshal(), BUFSIZE) < 0) {
            perror("Error sending from server\n"); 
            exit(EXIT_FAILURE);
        }
        
    }
    printf("Closing Server ...\n");   
}