CC = g++
ARGS = -Wall

all: udpserver udpclient
udpserver: smain.cpp
	$(CC) $(ARGS) -o server smain.cpp server.cpp UDPserverSocket.cpp
udpclient: cmain.c
	$(CC) $(ARGS) -o client cmain.cpp client.cpp UDPclientSocket.cpp

clean:
	rm -f *.o udpserver udpclient *~