#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/array.hpp>

#include "Server.h"

int main(int argc, const char* argv[]){
    int i = 0, j = 0;
    int port;
    //getting dimension of map. if not provided, default is 10x10
    if(argc != 2){
        port = 7777;
    }
    else{
        port = atoi(argv[1]);
    }

     
    try{
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        
        Server(io_service, endpoint);
        
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }   
    std::cout << "Proxy Server Closed";

    return 0;
}
