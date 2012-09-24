CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror
RELEASE_FLAGS = -O2
OUTPUT_PATH = target/
SOURCE_PATH = src/


dev: 
	make clean; make all; clear; ./$(OUTPUT_PATH)TCPEchoServer4 5000

release : 
	make clean; git add .; git commit; git push


all : server client 

server : 
	gcc -std=gnu99 $(SOURCE_PATH)TCPEchoServer4.c $(SOURCE_PATH)mylib.c $(SOURCE_PATH)DieWithMessage.c $(SOURCE_PATH)TCPServerUtility.c $(SOURCE_PATH)AddressUtility.c -o $(OUTPUT_PATH)TCPEchoServer4
	
client : 
	gcc -std=gnu99 $(SOURCE_PATH)TCPEchoClient4.c $(SOURCE_PATH)DieWithMessage.c $(SOURCE_PATH)AddressUtility.c -o $(OUTPUT_PATH)TCPEchoClient4

clean :
	rm log.net;rm $(OUTPUT_PATH)/*
