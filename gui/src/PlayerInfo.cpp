
#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(int winSizeX, int winSizeY)
: _rect(winSizeX - 334, winSizeY - 166, 334, 166)
{
    _posX = winSizeX - 334;
    _posY = winSizeY - 166;
    
    _rect.loadTexture("res/textures/player_infos.png", true);
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
    std::list<int>	list = _player->getRecourse();
    unsigned int	resourceAmmount[7];
    unsigned int	level = _player->getLevel();
    int 			space = 0;
    int				i = 0;
    
    std::memset(resourceAmmount, 0, sizeof(unsigned int) * 7);
    
    for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
        resourceAmmount[i++] = (*it);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    _rect.draw(shader);
    
    ss << level;
    tempText.setText(std::string("Level:") + ss.str(), _posX + 10, _posY + 30);
    tempText.draw(shader);
    ss.str("");
    
    ss << resourceAmmount[0];
    tempText.setText(ss.str(), _posX + 120, _posY + 65);
    tempText.draw(shader);
    ss.str("");
    
    for (i = 1; i <= 3; ++i)
    {
        if (i == 1)
            space = 50;
        else
            space = (i * 50) + (27 * (i - 1));
        
        ss << resourceAmmount[i];
        
        tempText.setText(ss.str(), _posX + space, _posY + 100, 30);
        tempText.draw(shader);
        ss.str("");
    }
    for (i = 1; i <= 3; ++i)
    {
        if (i == 1)
            space = 50;
        else
            space = (i * 50) + (27 * (i - 1));
        
        ss << resourceAmmount[i + 2];
        
        tempText.setText(ss.str(), _posX + space, _posY + 130, 30);
        tempText.draw(shader);
        ss.str("");
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void	PlayerInfo::update()
{
    if (_player != NULL)
        if (_player->getStatus() == Player::DYING)
        {
            _visible = false;
            _player = NULL;
        }
}

void	PlayerInfo::setPlayer(Player *selectedPlayer)
{
    _player = selectedPlayer;
}

Player	*PlayerInfo::getPlayer() const
{
    return (_player);
}

void	PlayerInfo::setVisible(bool visibility)
{
    _visible = visibility;
}

bool	PlayerInfo::isVisible() const
{
    return (_visible);
}