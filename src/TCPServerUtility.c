#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "Practical.h"
#include "mylib.h"
#include "llist.h"
#include "Napster.h"

static const int MAXPENDING = 5; // Maximum outstanding connection requests

void string_free(void *a){
    char *a1=(char *)a;
    free(a1);
}
int compareNapsterNodes(void *a, void *b){
    napsterNode *a1=(napsterNode *)a;
    napsterNode *b1=(napsterNode *)b;

    if (sameString(a1->address, b1->address) && sameString(a1->filename, b1->filename)){
        return 1;
    }
    else{
        return 0;
    }
}

void listFiles(llist *dataList, int clntSocket){
    char *retBuff=malloc(sizeof(char)*strlen("Files are:\n"));
    strcpy(retBuff,"Files are:\n");
    resetIterator(dataList);
    napsterNode *index;
    Node *check=nextElement(dataList);
    if (check){
        index=(napsterNode *)check->data;
    }
    else{
        return;
    }
    while(index){
        char *newLine=malloc(sizeof(char)*(strlen(index->address)+strlen(index->filename)+3));
        strcat(newLine,index->address);
        strcat(newLine," ");
        strcat(newLine,index->filename);
        strcat(newLine,"\n");
        retBuff=realloc(retBuff, (strlen(retBuff)+strlen(newLine)+1));
        strcat(retBuff, newLine);
        check=nextElement(dataList);
        if(check){
            index=(napsterNode *)check->data;
        }
        else{
            index=NULL;
        }
    }
    ssize_t numBytesSent = send(clntSocket, retBuff, (sizeof(char)*strlen(retBuff)), 0);
        if (numBytesSent < 0)
          DieWithSystemMessage("send() failed");
            close(clntSocket); // Close client socket
            return;
}
void removeFile(llist *argList, llist *dataList, char *ipAddr){
    char *nextArg=deQueue(argList);
    napsterNode *testNode=(napsterNode *)malloc(sizeof(napsterNode));
    testNode->address=ipAddr;
    while(nextArg){
        testNode->filename=nextArg;
        removeFromList(dataList, findInList(dataList, testNode, compareNapsterNodes), string_free);
        nextArg=deQueue(argList);
    }
    free(testNode);
    resetIterator(argList);
}
void addFile(llist *argList, llist *dataList, char *ipAddr){
    char *nextArg=deQueue(argList);
    if (sameString(nextArg, "-d")){
        removeFile(argList, dataList, ipAddr);
        resetIterator(argList);
        return;
    }
    while(nextArg){
        napsterNode *node=(napsterNode *)malloc(sizeof(napsterNode));
        char *nextArgMalloced=(char *)malloc(sizeof(char)*strlen(nextArg));
        char *ipAddrMalloced=(char *)malloc(sizeof(char)*strlen(ipAddr));
        strcpy(nextArgMalloced, nextArg);
        strcpy(ipAddrMalloced,ipAddr);
        node->filename=nextArgMalloced;
        node->address=ipAddrMalloced;
        addToList(dataList, node);
        nextArg=deQueue(argList);
    }
    resetIterator(argList);
}

int SetupTCPServerSocket(const char *service) {
  // Construct the server address structure
  struct addrinfo addrCriteria;                   // Criteria for address match
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  addrCriteria.ai_flags = AI_PASSIVE;             // Accept on any address/port
  addrCriteria.ai_socktype = SOCK_STREAM;         // Only stream sockets
  addrCriteria.ai_protocol = IPPROTO_TCP;         // Only TCP protocol

  struct addrinfo *servAddr; // List of server addresses
  int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

  int servSock = -1;
  for (struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next) {
    // Create a TCP socket
    servSock = socket(addr->ai_family, addr->ai_socktype,
        addr->ai_protocol);
    if (servSock < 0)
      continue;       // Socket creation failed; try next address

    // Bind to the local address and set socket to listen
    if ((bind(servSock, addr->ai_addr, addr->ai_addrlen) == 0) &&
        (listen(servSock, MAXPENDING) == 0)) {
      // Print local address of socket
      struct sockaddr_storage localAddr;
      socklen_t addrSize = sizeof(localAddr);
      if (getsockname(servSock, (struct sockaddr *) &localAddr, &addrSize) < 0)
        DieWithSystemMessage("getsockname() failed");
      fputs("Binding to ", stdout);
      PrintSocketAddress((struct sockaddr *) &localAddr, stdout);
      fputc('\n', stdout);
      break;       // Bind and listen successful
    }

    close(servSock);  // Close and try again
    servSock = -1;
  }

  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);

  return servSock;
}

int AcceptTCPConnection(int servSock) {
  struct sockaddr_storage clntAddr; // Client address
  // Set length of client address structure (in-out parameter)
  socklen_t clntAddrLen = sizeof(clntAddr);

  // Wait for a client to connect
  int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
  if (clntSock < 0)
    DieWithSystemMessage("accept() failed");

  // clntSock is connected to a client!

  fputs("Handling client ", stdout);
  PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
  fputc('\n', stdout);

  return clntSock;
}

void HandleTCPClient(int clntSocket, char *ipAddr, llist *dataList) {
  char buffer[BUFSIZE]; // Buffer for echo string

  // Receive message from client
  ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
  if (numBytesRcvd < 0)
    DieWithSystemMessage("recv() failed");
    llist *argList=newList();
    buffer[numBytesRcvd]='\0';
    split(buffer, argList);
    char *funcArg=deQueue(argList);
    if (sameString(funcArg, "ADDFILE")){
        addFile(argList, dataList, ipAddr);
    }
    else if (sameString(funcArg, "LISTFILES")){
        listFiles(dataList, clntSocket);
        return;
    }
  // Send received string and receive again until end of stream
  while (numBytesRcvd > 0) { // 0 indicates end of stream
    // Echo message back to client
    ssize_t numBytesSent = send(clntSocket, "Success\n", numBytesRcvd, 0);
    if (numBytesSent < 0)
      DieWithSystemMessage("send() failed");

    // See if there is more data to receive
    numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0)
      DieWithSystemMessage("recv() failed");
  }

  close(clntSocket); // Close client socket
}
