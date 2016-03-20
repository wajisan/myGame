#include "Client.h"
 
Client::Client()
{
  this->Init();
}

int	Client::Init()
{
  this->sock = socket(AF_INET , SOCK_STREAM , 0);
  if (this->sock == -1)
    {
      std::cerr << "Could not create socket" << std::endl;
      return (1);
    }
  std::cout << "Socket created" << std::endl;

  this->server.sin_addr.s_addr = inet_addr("127.0.0.1");
  this->server.sin_family = AF_INET;
  this->server.sin_port = htons( 8888 );

  if (connect(this->sock , (struct sockaddr *)&this->server , sizeof(this->server)) < 0)
    {
      std::cerr << "Error : Connect Failed" << std::endl;
      return (1);
    }
  std::cout << "Connected" << std::endl;
  return (0);
}

int	Client::Run()
{
  char			message[1000];
  char			server_reply[2000];

  if (this->sock == -1)
    return (1);

  while (1)
    {
      std::cout << "Please press one of the good letter : ";
      scanf("%s", message);///separe words , need change

      if (send(this->sock, message, strlen(message), 0) < 0)
        {
	  std::cerr << "Send failed" << std::endl;
	  return (1);
        }
      memset(server_reply, 0, 2000);//clear
      if (recv(sock ,server_reply, 2000, 0) < 0)
        {
	  std::cerr << "Recv failed" << std::endl;
	  break;
        }
      std::cout << "Server : ";
      puts(server_reply);
    }
  close(this->sock);
  return (0);
}

