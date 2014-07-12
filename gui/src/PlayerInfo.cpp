
#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(int winSizeX, int winSizeY)
: _rect(winSizeX - 334, winSizeY - 166, 334, 166)
{
    _posX = winSizeX - 334;
    _posY = winSizeY - 166;
    
    _rect.loadTexture("res/textures/player_infos.png");
    _rect.build();
    
    _visible = false;
    _player = NULL;
}

PlayerInfo::~PlayerInfo()
{
    
}

void	PlayerInfo::draw(Shader *shader)
{
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
        
        tempText.setText(ss.str(), _posX + space, _posY + 10, 30);
        tempText.draw(shader);
        ss.str("");
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void	PlayerInfo::setGround(Ground *selectedGround)
{
    _ground = selectedGround;
}

Ground	*PlayerInfo::getGround() const
{
    return (_ground);
}

void	PlayerInfo::setVisible(bool visibility)
{
    _visible = visibility;
}

bool	PlayerInfo::isVisible() const
{
    return (_visible);
}