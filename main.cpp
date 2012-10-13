#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <boost/asio.hpp>
#include <fstream>

#include "Server.h"

int main(int argc, const char* argv[]){
    int i = 0, j = 0;
    int port;
    size_t pos;
    std::ifstream infile;
    std::vector <std::string *> filters;
    std::string * tmp_filter_pointer;
    char filter[100];

    if(argc < 2){
        port = 7777;
    }
    else{
        port = atoi(argv[1]);
    }
    
    if(argc == 3){
        infile.open(argv[2], std::ifstream::in);
    }
    else{
        infile.open("filter.dat", std::ifstream::in);
    }

    if(!infile.is_open()){
        std::cerr << "Filter file not found!" << std::endl;
    }
    else{
        while(!infile.eof()){
            infile.getline(filter, 100);
            if(strlen(filter) > 0){
                tmp_filter_pointer = new std::string(filter);
                filters.push_back(tmp_filter_pointer);
            }
            
        }
    }
    
    infile.close();


    try{
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        
        Server(io_service, endpoint, filters);
        
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Proxy Server Closed";
    for(i = filters.size() - 1; i >= 0; i--){
        delete filters[i];
        filters.pop_back();
    }

    return 0;
}
