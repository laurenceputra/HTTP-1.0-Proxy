all: proxy

proxy: main.o Server.o Connection.o
	g++ -g -L/usr/local/Cellar/boost/1.50.0/lib -lboost_thread-mt -lboost_date_time-mt -lboost_iostreams-mt -lboost_system-mt main.o Server.o Connection.o -o proxy

main.o: main.cpp
	g++ -g -c main.cpp

Server.o: Server.cpp
	g++ -g -c Server.cpp

Connection.o: Connection.cpp
	g++ -g -c Connection.cpp
