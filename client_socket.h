#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <string>
#include <ostream>
#include <iostream>

#define MAXLINE 2048 

class aquaclientsocket
{
public:
    int sockfd; 
    char buffer[MAXLINE];  
    struct sockaddr_in servaddr;
    int n, broadcastEnable, ret;
    unsigned int len;

    aquaclientsocket(std::string typeofsocket, int port);
    void send(std::string message);
};