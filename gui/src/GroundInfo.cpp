
#include "utils.hpp"
#include "GroundInfo.hpp"

GroundInfo::GroundInfo(int winSizeX, UNUSED int winSizeY)
: _rect(winSizeX / 2 - (556 / 2), 0, 556, 50)
{
    _posX = winSizeX / 2 - (556 / 2);
    _posY = 0;
    
    _rect.loadTexture("res/textures/on_top_map.png");
    _rect.build();
    
    _visible = false;
    _ground = NULL;
}

GroundInfo::~GroundInfo()
{
    
}

void	GroundInfo::draw(Shader *shader)
{
    if (_ground == NULL)
        return ;
    
    std::stringstream	ss;
    
    FontText		tempText;
    std::list<int>	list = _ground->getRecourse();
    unsigned int	resourceAmmount[7];
    int 			space = 0;
    int				i = 0;
    
    std::memset(resourceAmmount, 0, sizeof(unsigned int) * 7);
    
    for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
        resourceAmmount[i++] = (*it);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    _rect.draw(shader);
    for (i = 1; i <= 7; ++i) {
        if (i == 1)
            space = 50;
        else
            space = (i * 50) + (27 * (i - 1));
        
        ss << resourceAmmount[i - 1];
        
        tempText.setText(ss.str(), _posX + space, _posY + 10, 31);
        tempText.draw(shader);
        ss.str("");
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void	GroundInfo::update()
{
    if (_ground == NULL)
        _visible = false;
}

void	GroundInfo::setGround(Ground *selectedGround)
{
    _ground = selectedGround;
}

Ground	*GroundInfo::getGround() const
{
    return (_ground);
}

void	GroundInfo::setVisible(bool visibility)
{
    _visible = visibility;
}

bool	GroundInfo::isVisible() const
{
    return (_visible);
}