#include "Sfml.hpp"

extern "C"
{
#include "network.h"
}

int	main(__attribute__ ((__unused__)) int ac,
         __attribute__ ((__unused__)) char **av)
{
  Sfml	lib(500, 500);
  t_net	*client;

  client = create_connection("::1", "4242", SOCK_STREAM, &connect_nb);
  if (!client)
    return (1);
  int status;
  std::cout << "Connecting . ";
  while ((status = is_connected(client)))
    {
      usleep(500);
      std::cout << ".";
    }
  if (status == -1)
    {
      std::cerr << "Error on connection" << std::endl;
      return (1);
    }

    char buff[500];
    int a = read(client->socket, buff, sizeof(buff) - 1);
    buff[a] = '\0';
    std::cout << buff << std::endl;

  lib.putText("Bonjour Fabulus!", 50, 50, 12, WHITE);
  lib.putText(buff, 50, 62, 12, WHITE);
  lib.waitThread();
  return 0;
}
