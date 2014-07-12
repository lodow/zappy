
#ifndef PLAYERINFO_HPP_
# define PLAYERINFO_HPP_

# include <map>
# include "Ground.hpp"
# include "FontText.hpp"
# include "Rectangle.hpp"

class PlayerInfo
{
public:
    PlayerInfo(int winSizeX, int winSizeY);
    virtual ~PlayerInfo();
    
    void	draw(Shader *shader);
    
    void	setGround(Ground *selectedGround);
    Ground	*getGround() const;
    
    void	setVisible(bool visibility);
    bool	isVisible() const;
    
private:
    Ground		*_ground;
    Rectangle	_rect;
    
    int		_posX;
    int		_posY;
    bool	_visible;
};

#endif