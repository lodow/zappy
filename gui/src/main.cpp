
#include "GameEngine.hpp"

int	main(UNUSED int ac, UNUSED char **av)
{
    signal(SIGPIPE, SIG_IGN);

    GameEngine	lib(800, 600);
    return 0;
}
