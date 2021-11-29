/*
To test the reliability of datagrams, we tried sending a message with legnth longer than the buffer size. 
The message recived by the server was croped to match the buffer size. For example: 
We sett BUFSIZE to 4 and sent a message of 0123456789
The server received and echoed only 012 to the client because marshalling increases the size of the message, and 
every 3 bytes in the original message are represented using 4 bytes. In unmarshalling, every 4 bytes are represented by 3 bytes. 
This experiment shows that UDP has issues with reliability backet loss.  
*/
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