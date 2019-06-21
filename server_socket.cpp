#include "server_socket.h"

void aquaserversocket::ordreArrosage(int relais, std::string trame, int port)
    {
        if(sBuffer == trame && port == 3256)
        {
            wiringPiSetupPhys();
            pinMode(relais,OUTPUT);
            std::cout << "ok" << std::endl;
            digitalWrite(relais,LOW);
            std::cout << "electrovanne allumée" << std::endl;
            std::cout << "début arrosage" << std::endl;
        }
    }

aquaserversocket::aquaserversocket(std::string typeofsocket, int port)
{
	std::cout << "Creation du server '" << typeofsocket << "' sur le port " << port << std::endl;
	// Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
    
    int optval = 1;
    setsockopt(sockfd,SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
      
    // Filling serverordreArrosage(RELAY_1,"110000000",); information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(port); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    doThings(port);
}

void aquaserversocket::doThings(int port)
{
	for(;;)
	{
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0';
    sBuffer = buffer;
    std::cout << "Client " << " Trame : " << sBuffer << std::endl;

    ordreArrosage(RELAY_1,"110000000", port);
    ordreArrosage(RELAY_2,"001100000", port);
    ordreArrosage(RELAY_3,"000011000", port);
    ordreArrosage(RELAY_4,"000000110", port);

    if(sBuffer == "000000000" && port == 3256)
    {
        digitalWrite(RELAY_1,HIGH);
        digitalWrite(RELAY_2,HIGH);
        digitalWrite(RELAY_3,HIGH);
        digitalWrite(RELAY_4,HIGH);
        
        
        std::cout << "fin arrosage, electrovanne eteinte" << std::endl;
    }
    
    }
}
