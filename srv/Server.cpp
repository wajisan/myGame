#include "Server.h"

bool		check(std::string str)
{
  std::string letter;
  std::ifstream file("srv/letter.txt");

  if (file)
    {
      while (std::getline(file, letter))
	{
	  if (str == letter)
	    return true;
	}
    }
  return false;
}

void		*Connect(void *socket_desc)
{
  int		sock = *(int*)socket_desc;
  int		read_size;
  char		*message;
  char		cmsg[2000];
  std::string	str;
     
  while ((read_size = recv(sock , cmsg , 2000 , 0)) > 0 )
    {
      cmsg[read_size] = '\0';
      str = cmsg;
      if (check(str))
	write(sock , "Nice!" , 5);
      else
	write(sock , "Wrong!" , 6);

      std::cout << "Client (" << sock << "): " << cmsg << std::endl;
      memset(cmsg, 0, 2000);//clear
    }
  if (read_size == 0)
    {
      std::cout << "Client (" << sock << ") disconnected" << std::endl;
      fflush(stdout);
    }
  else if (read_size == -1)
    std::cerr << "Error with receive" << std::endl;
  return 0;
}

Server::Server()
{
  this->Init();
}

int	Server::Init()
{
  this->socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (this->socket_desc == -1)
    std::cerr << "Error socket" << std::endl;
  std::cout << "Socket is create" << std::endl;

  this->server.sin_family = AF_INET;
  this->server.sin_addr.s_addr = INADDR_ANY;
  this->server.sin_port = htons( 8888 );
     
  if (bind(this->socket_desc,(struct sockaddr *)&this->server , sizeof(this->server)) < 0)
    {
      std::cerr << "Error with bind" << std::endl;
      return 1;
    }
  std::cout << "Bind is done" << std::endl;
     
  listen(this->socket_desc , 3);
  std::cout << "Ready to connect" << std::endl;
}

int	Server::Run()
{
  int	c;

  c = sizeof(struct sockaddr_in);
  while ((this->client_sock = accept(this->socket_desc, (struct sockaddr *)&this->client, (socklen_t*)&c)))
    {
      std::cout << "Connected" << std::endl;
      if (pthread_create( &this->thread_id, NULL, Connect, (void*) &this->client_sock) < 0)
        {
	  std::cerr << "Error with thread" << std::endl;
	  return 1;
        }
      std::cout << "Handler assigned" << std::endl;
    }
 
  if (this->client_sock < 0)
    {
      std::cerr << "Error with accept" << std::endl;
      return 1;
    }
  return 0;
}

