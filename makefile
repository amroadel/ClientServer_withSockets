CC = g++
ARGS = -Wall

all: udpserver udpclient
udpserver: smain.cpp
	$(CC) $(ARGS) -g -o server.o smain.cpp server.cpp UDPserverSocket.cpp
udpclient: cmain.cpp
	$(CC) $(ARGS) -g -o client.o cmain.cpp client.cpp UDPclientSocket.cpp

clean:
	rm -f *.o udpserver udpclient *~