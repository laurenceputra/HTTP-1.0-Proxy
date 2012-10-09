#include "Connection.h"
#include <iostream>
#include <sstream>

Connection::Connection(boost::asio::io_service& io_service) : client_socket(io_service){
	input_stream = "";
    output_stream = "";
}

boost::asio::ip::tcp::socket& Connection::get_socket(){
    return client_socket;
}

Connection::~Connection(){
    std::cout <<  "~~~~~~~~~~~~~~Connection Closed~~~~~~~~~~~~~~" << std::endl;
}

void Connection::start(){
    //spawn a new thread to handle each new incoming connection
    boost::thread client_thread(boost::bind(&Connection::thread_process, this));
    //stall processing until thread is done
    client_thread.join();
}

void Connection::thread_process(){
    size_t pos, length;
    boost::system::error_code error;
    int read_amount;
    std::cout << "~~~~~~~~~~~~~~Connection Started~~~~~~~~~~~~~~" << std::endl;
    //gets only the first row
    while(input_stream.find("\r\n") == std::string::npos){
        client_socket.read_some(boost::asio::buffer(input_buffer, 512));
        input_stream.append(input_buffer);
    }
    
    pos = input_stream.find("\r\n");
    input_stream.erase(pos + 1);

    pos = input_stream.find(" ");
    type = input_stream.substr(0, pos);
    if(pos == std::string::npos && type.compare("GET") != 0){
        handle_error("405");
        exit;
    }
    input_stream.erase(0, pos + 1);
    pos = input_stream.find(" ");
    url = input_stream.substr(0, pos);

    if(pos == std::string::npos){
        handle_error("400");
        exit;
    }
    //split url into host and resource
    pos = url.find("//");
    host = url.substr(pos + 2);
    pos = host.find("/");
    resource = host.substr(pos);
    host.erase(pos);

    std::cout << url << std::endl;
    second_io_service = boost::shared_ptr<boost::asio::io_service>(new boost::asio::io_service);
    boost::asio::ip::tcp::resolver resolver(*second_io_service);
    boost::asio::ip::tcp::resolver::query query(host, "80");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    second_socket = boost::shared_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(*second_io_service));
    boost::system::error_code _error = boost::asio::error::host_not_found;
    while(_error && endpoint_iterator != end) {
        second_socket->close();
        second_socket->connect(*endpoint_iterator++, _error);
    }

    output_stream = "GET ";
    output_stream += url;
    output_stream += " HTTP/1.0\r\n\r\n";
    boost::asio::write(*second_socket, boost::asio::buffer(output_stream));

    //read headers
    input_stream = "";
    while(input_stream.find("\r\n\r\n") == std::string::npos){
        (*second_socket).read_some(boost::asio::buffer(input_buffer, 1));
        input_stream += input_buffer[0];
    }
    boost::asio::write(client_socket, boost::asio::buffer(input_stream));
    std::cout << input_stream << std::endl;
    //get content length
    pos = input_stream.find("Content-Length: ");
    content_length = input_stream.substr(pos + 16);

    pos = content_length.find("\r\n");
    content_length.erase(pos);
    int_content_length = atoi(content_length.data());
    if(int_content_length == 0){
        int_content_length = -1;
    }
    length = 8192;
    //read content
    while(length == 8192 && !error){
        std::cout << length << std::endl;
        try{
            length = (*second_socket).read_some(boost::asio::buffer(input_buffer, 8192), error);
        }
        catch(std::exception& e){
            std::cout << e.what();
            length = 0;
        }
        input_stream = input_buffer;
        boost::asio::write(client_socket, boost::asio::buffer(input_stream, length));
        //std::cout << input_stream;
    }
    std::cout << std::endl;
    client_socket.close();
}

void Connection::handle_error(char* error){
    output_stream = "HTTP status: ";
    output_stream += error;
    boost::asio::write(client_socket, boost::asio::buffer(output_stream));
}