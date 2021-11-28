#include <stdio.h>
#include "server.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port; 
    server s1("xyz", port); 
    s1.serveRequest();
    return 0;
}