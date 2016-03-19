all: server client

server: srv/Server.cpp srv/mains.cpp
	g++ -o server srv/Server.cpp srv/mains.cpp -lpthread

client: clt/Client.cpp clt/mainc.cpp
	g++ -o client clt/Client.cpp clt/mainc.cpp
