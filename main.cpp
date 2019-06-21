#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include <cmath>
#include <wiringPi.h>

#include "server_socket.h"
#include "client_socket.h"

using namespace std;
using namespace rapidjson;

boost::mutex a;

void initSocket()
{
    aquaserversocket initSocket("init",3256);
}

void telSocket()
{
    aquaclientsocket telSocket("telephone",3258);
    telSocket.send("111000000");
}

void arret()
{
    aquaclientsocket stop("arret",3258);
    stop.send("0");
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    stop.send("1");
}


int main(int argc, char* argv[])
{
    wiringPiSetupPhys();
    pinMode(RELAY_1,OUTPUT);
    pinMode(RELAY_2,OUTPUT);
    pinMode(RELAY_3,OUTPUT);
    pinMode(RELAY_4,OUTPUT);
    
    boost::thread init(&initSocket);
    boost::thread tel(&telSocket);
    boost::thread stop(&arret);

    init.join();
    tel.join();

}
