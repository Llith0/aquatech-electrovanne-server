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
#include <wiringPi.h>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#define RELAY_1 11
#define RELAY_2 13
#define RELAY_3 15
#define RELAY_4 7
#define MAXLINE 2048 

class aquaserversocket 
{
public :
	int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr, cliaddr;
    int n;
    unsigned len;
    std::string sBuffer;

    aquaserversocket(std::string typeofsocket, int port);
    void doThings(int port);
    void ordreArrosage(int relais, std::string trame, int port);


};
