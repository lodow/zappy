
#ifndef FONTTEXT_HPP_
# define FONTTEXT_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/OpenGL.hpp>
# include <glm/glm.hpp>
# include "IEntity.hpp"

# define FONT_PATH	"res/font/Monospace.ttf"

class FontText : public IEntity
{
public:
    FontText(const glm::vec2 &pos, const std::string &msg, int size, sf::Color color);
    virtual ~FontText();
    
    const glm::vec2 &getPos() const;
    
    void draw(sf::RenderWindow &window) const;
    void draw(Shader *shader) {};

private:
    sf::Text _text;
    sf::Font _font;
    
    glm::vec2 _pos;
};

#endif /* FONTTEXT_HPP_ */
