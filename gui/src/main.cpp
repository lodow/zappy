#include "GameEngine.hpp"

int	main(UNUSED int ac, UNUSED char **av)
{
  try {
      GameEngine	lib(1920, 1080);
  }
  catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
  }
    return 0;
}
