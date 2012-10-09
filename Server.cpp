#include "Server.h"
#include <iostream>

Server::Server(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) : boost_io_service(io_service), tcp_acceptor(io_service, endpoint){

	boost::shared_ptr<Connection> new_connection(new Connection(boost_io_service));
	tcp_acceptor.async_accept((*new_connection).get_socket(),
		boost::bind(&Server::accept_handler, this, new_connection, boost::asio::placeholders::error));
	boost_io_service.run();
}
Server::~Server(){
	//this should never show up
	std::cout << "Server DIED" << std::endl;
}
void Server::accept_handler(boost::shared_ptr<Connection> connection, const boost::system::error_code& error){
	if(!error){
		std::cout << "New Server Connection Accepted!" << std::endl;
		(*connection).start();
		boost::shared_ptr<Connection> new_connection(new Connection(boost_io_service));
		tcp_acceptor.async_accept((*new_connection).get_socket(),
			boost::bind(&Server::accept_handler, this, new_connection, boost::asio::placeholders::error));
	}
	else{
		std::cout << error.message() << std::endl;
	}
}