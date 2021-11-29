#include <stdio.h>
#include "client.h"

int main(int argc, char **argv) {

    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(EXIT_FAILURE);
    }

    char *hostname = argv[1];
    int port = atoi(argv[2]);

    client c1(hostname, port); 
    c1.execute();
    return 0;
}