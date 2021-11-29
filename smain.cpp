#include <stdio.h>
#include "server.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    char hostname[] = "localhost";
    int port = atoi(argv[1]);
    server s1(hostname, 8888); 
    s1.serveRequest();
    return 0;
}