#ifndef CONNECTION
#define CONNECTION
#include <string>
#include <vector>
#include <stdlib.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>

class Connection : public boost::enable_shared_from_this<Connection>{
    public:
        Connection(boost::asio::io_service& io_service, std::vector <std::string*> new_filters);
        ~Connection();
        boost::asio::ip::tcp::socket& get_socket();
        void thread_process();
        void handle_client_read(const boost::system::error_code& error);
        void handle_server_read(const boost::system::error_code& error);
        void handle_error(std::string error);

    private:
        bool running;
        boost::shared_ptr<boost::asio::io_service> second_io_service;
        boost::shared_ptr<boost::asio::ip::tcp::socket> second_socket;
        boost::asio::ip::tcp::socket client_socket;
        boost::thread client_thread;
        char input_buffer[8192];
        std::string input_stream;
        std::string output_stream;
        std::string type;
        std::string url;
        std::string host;
        std::string resource;
        std::string port;
        std::vector <std::string*> filters;
};

#endif