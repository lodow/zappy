#include "Sfml.hpp"

int	main(int ac, char **av)
{
  Sfml	lib(500, 500);

  lib.putText("Bonjour Fabulus!", 50, 50, 12, WHITE);
  lib.putText("Bonjour Fabulus!", 50, 62, 12, WHITE);
  lib.waitThread();
  return 0;
}
