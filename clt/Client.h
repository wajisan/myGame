#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


class Client
{
  int			sock;
  struct sockaddr_in	server;

public:
  Client();
  int	Init();
  int	Run();
};

#endif // CLIENT_H
