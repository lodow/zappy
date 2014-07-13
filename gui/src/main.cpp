#include <signal.h>
#include <iostream>
#include <exception>
#include <stdexcept>

#include "GameEngine.hpp"

uint64_t cpu_cycle()
{
  unsigned int lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return (((uint64_t)hi << 32) | lo);
}

int	main(int argc, char **argv)
{
  try
    {
      if (argc > 2)
        {
          signal(SIGPIPE, SIG_IGN);
          srand(cpu_cycle());

          GameEngine graphic(1640, 1024);

          if (!graphic.initConnection(argv[1], argv[2]))
            throw std::runtime_error("Connection failed");

          graphic.initOpenGL();

          graphic.run();
        }
        else
            std::cout << "Usage: ./graphic host port" << std::endl;

    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  return 0;
}

