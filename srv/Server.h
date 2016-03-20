#ifndef SERVER_H
#define SERVER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

class Server
{
  int			socket_desc;
  int			client_sock;
  struct sockaddr_in	server;
  struct sockaddr_in	client;
  pthread_t		thread_id;
 public:
  Server();
  int	Init();
  int	Run();
};

void	*Connect(void*);

#endif // SERVER_H
