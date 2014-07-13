
#ifndef PLAYERINFO_HPP_
# define PLAYERINFO_HPP_

# include <map>
# include "Player.hpp"
# include "FontText.hpp"
# include "Rectangle.hpp"

class PlayerInfo
{
public:
    PlayerInfo(int winSizeX, int winSizeY);
    virtual ~PlayerInfo();
    
    void	draw(Shader *shader);
    
    void	setPlayer(Player *selectedPlayer);
    Player	*getPlayer() const;
    
    void	setVisible(bool visibility);
    bool	isVisible() const;
    
private:
    Player		*_player;
    Rectangle	_rect;
    
    int		_posX;
    int		_posY;
    bool	_visible;
};

#endif