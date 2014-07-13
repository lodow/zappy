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
    if (argc > 2)
    {
        try
        {
            signal(SIGPIPE, SIG_IGN);
            srand(cpu_cycle());

            GameEngine graphic(800, 600);

            if (!graphic.initConnection(argv[1], argv[2]))
                throw std::runtime_error("Connection failed");

            graphic.initOpenGL();

            graphic.run();

        } catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
