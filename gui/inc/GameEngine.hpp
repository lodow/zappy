
#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
# else
#   ifndef GL_GLEXT_PROTOTYPES
#    define GL_GLEXT_PROTOTYPES
#   endif
#  include <GL/gl.h>
#  include <GL/glext.h>
# endif

# include <glm/glm.hpp>
# include <glm/gtx/transform.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <list>
# include <string>
# include <exception>
# include "utils.hpp"
# include "Model.hpp"
# include "Camera.hpp"
# include "IEntity.hpp"
# include "Cube.hpp"
# include "Gem.hpp"
# include "Ground.hpp"
# include "Map.hpp"

extern "C"
{
#include "ring_buffer.h"
#include "select.h"
#include "network.h"
#include "liste.h"
}

# define WINDOW_NAME	"ZAPPY"
# define FPS            60

# include "Parser.hpp"

class GameEngine {

typedef std::list<Map::Players::iterator> Deads;

private:
    Camera            _camera;
    Cube              *_cube;
    Gem				  *_gem;
    
    sf::RenderWindow  _window;
    
    Map               _map;
    t_net             *_client;
    t_list            *_elem;
    struct timeval    _tv;
    Parser            *_parser;
    Player *_player;
    
public:
    GameEngine(const int&, const int&);
    ~GameEngine();
    
    void	run();
};

int handle_server(t_selfd *fd, void *serv);

#endif /* !GAMEENGINE_ */
