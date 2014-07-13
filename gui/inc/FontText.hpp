
#ifndef _FONTTEXT_H_
# define _FONTTEXT_H_

# include <string>
# include <SFML/Graphics.hpp>
# include <sstream>
# include "Geometry.hpp"
# include "AObject.hpp"

# define FONT "res/textures/font.tga"

class	FontText: public AObject
{
public:
    FontText();
    virtual ~FontText();
    
    void	draw(Shader *shader);
    void	clear();
    
    void	setText(std::string const& str, float x, float y, float size = 40.0f);
    
    template <typename T>
    std::string		operator<<(T const& in)
    {
        std::stringstream	ss;
        
        ss << in;
        setText(ss.str(), _defX, _defY, _defSize);
        
        return (ss.str());
    }
    
private:
    float				_defX;
    float				_defY;
    float				_defSize;
    
    sf::Texture			_font;
    Geometry			*_geometry;
};

#endif /* _FONTTEXT_H_ */
