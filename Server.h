#ifndef SERVER
#define SERVER
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>

#include "Connection.h"


class Server : public boost::enable_shared_from_this<Server>{
	public:
		Server(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint, std::vector <std::string*> new_filters);
		~Server();
		void accept_handler(boost::shared_ptr<Connection>, const boost::system::error_code&);

	private:
		std::vector <std::string*> filters;
		boost::asio::io_service& boost_io_service;
		boost::asio::ip::tcp::acceptor tcp_acceptor;
};

#endif