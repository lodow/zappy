
#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# include <GL/gl.h>
# include <glm/glm.hpp>
# include <glm/gtx/transform.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <list>
# include <string>
# include "utils.hpp"
# include "Model.hpp"
# include "Camera.hpp"
#include "Cube.hpp"

extern "C"
{
#include "ring_buffer.h"
#include "select.h"
#include "network.h"
#include "liste.h"
}

# define UNUSED         __attribute__ ((__unused__))
# define WINDOW_NAME	"ZAPPY"
# define FPS            60

typedef std::list<sf::Text> TextList;
typedef std::list<IEntity *> Map;

# include "Parser.hpp"

class GameEngine {
private:
    Camera            _camera;
    Cube              *_cube;
    
    sf::RenderWindow  _window;
    sf::Font          _font;
    
    TextList          _texts;
    Map               _map;
    t_net             *_client;
    t_list            *_elem;
    struct timeval    _tv;
    Parser            *_parser;
    
public:
    GameEngine(const int&, const int&);
    ~GameEngine();
    
    void	run();
};

int handle_server(t_selfd *fd, void *serv);

#endif /* !GAMEENGINE_ */
