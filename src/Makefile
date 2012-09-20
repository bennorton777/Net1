CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror
RELEASE_FLAGS = -O2

all : server client 

server : TCPEchoServer4.c DieWithMessage.c TCPServerUtility.c AddressUtility.c
	gcc -std=gnu99 TCPEchoServer4.c DieWithMessage.c TCPServerUtility.c AddressUtility.c -o TCPEchoServer4
	
client : TCPEchoClient4.c DieWithMessage.c AddressUtility.c
	gcc -std=gnu99 TCPEchoClient4.c DieWithMessage.c AddressUtility.c -o TCPEchoClient4

clean :
	rm *.o; rm TCPEchoServer4; rm TCPEchoClient4; clear
