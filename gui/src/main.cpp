#include <signal.h>
#include <iostream>
#include <exception>

#include "GameEngine.hpp"

uint64_t cpu_cycle()
{
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int	main(UNUSED int ac, UNUSED char **av)
{
  try
    {
      signal(SIGPIPE, SIG_IGN);
      srand(cpu_cycle());

      GameEngine lib(800, 600);
    } catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  return 0;
}
