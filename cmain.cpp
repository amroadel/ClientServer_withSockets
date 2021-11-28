#include <stdio.h>
#include "client.h"

int main(int argc, char **argv) {

    char *hostname;
    int port; 

    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }

    hostname = argv[1];
    port = atoi(argv[2]);

    int port; 
    client c1(hostname, port); 
    c1.execute();
    return 0;
}