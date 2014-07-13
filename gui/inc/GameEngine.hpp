
#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# ifndef GLM_FORCE_RADIANS
#  define GLM_FORCE_RADIANS
# endif

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
# else
#   ifndef GL_GLEXT_PROTOTYPES
#    define GL_GLEXT_PROTOTYPES
#   endif
#  include <GL/gl.h>
#  include <GL/glext.h>
# endif

# define WINDOW_NAME	"ZAPPY"
# define FPS            60

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <list>
# include <string>
# include "utils.hpp"
# include "Model.hpp"
# include "Camera.hpp"
# include "IEntity.hpp"
# include "Cube.hpp"
# include "Gem.hpp"
# include "Ground.hpp"
# include "Map.hpp"
# include "Parser.hpp"
# include "Pan.hpp"
# include "SkyBox.hpp"
# include "GroundInfo.hpp"
# include "PlayerInfo.hpp"

extern "C"
{
#include "ring_buffer.h"
#include "select.h"
#include "network.h"
#include "liste.h"
}

typedef std::list<Map::Players::iterator> Deads;

class GameEngine {
public:
    GameEngine(float x, float y);
    ~GameEngine();
    
    bool	initConnection(const std::string &host, const std::string &port);
    void	initOpenGL() const;
    void	run();

private:
    void	selectObject(const sf::Event &mouseEvent);
    
    sf::RenderWindow  	_window;
    float				_sizeX;
    float				_sizeY;

    Camera            	_camera;
    SkyBox				*_skybox;
    Pan					*_pan;
    Gem				  	*_gem;
    
    Shader				*_mainShader;
    Shader				*_textShader;
    
    GroundInfo			_groundInfo;
    PlayerInfo			_playerInfo;
    
    Map               	_map;
    t_net             	*_client;
    t_list            	*_elem;
    struct timeval    	_tv;
    Parser            	*_parser;
    Player 			  	*_player;
};

int handle_server(t_selfd *fd, void *serv);

#endif /* !GAMEENGINE_ */
