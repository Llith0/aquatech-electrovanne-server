#include "client_socket.h"

aquaclientsocket::aquaclientsocket(std::string typeofsocket, int port)
{
    std::cout << "Creation du client '" << typeofsocket << "' sur le port " << port << std::endl;
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    broadcastEnable=1;
    ret=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(port); 
    servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
}

void aquaclientsocket::send(std::string message)
{

    sendto(sockfd, message.c_str(), strlen(message.c_str()), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));  
    std::cout << "Trame envoyée !" << std::endl;
}
