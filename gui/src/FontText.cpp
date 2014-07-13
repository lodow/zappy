
#include "FontText.hpp"

FontText::FontText()
: AObject()
{
    _geometry = NULL;
    _defX = 0.0f;
    _defY = 0.0f;
    _defSize = 40.0f;
    
    _font.loadFromFile(FONT);
}

FontText::~FontText()
{
    clear();
}

void	FontText::clear()
{
    if (_geometry)
    {
        delete _geometry;
        _geometry = NULL;
    }
}

void	FontText::draw(Shader *shader)
{
    if (_geometry)
    {
        
        sf::Texture::bind(&_font);
        _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
    }
}

void	FontText::setText(std::string const& str, float x, float y, float size)
{
    float Letterx, Lettery, space = 0;
    
    clear();
    if (!str.length())
        return ;
    _geometry = new Geometry();
    
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        if (i > 0.5f)
            space = (i - (0.5f * i)) * size;
        
        Letterx = ((str[i] % 16) - 16 % 16) / 16.0f;
        Lettery = 1 - ((str[i] / 16) - 16 / 16) / 16.0f;

        _geometry->pushVertex(glm::vec3(x + space, y + size, 0));
        _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
        _geometry->pushVertex(glm::vec3(x + space, y, 0));
        _geometry->pushUv(glm::vec2(Letterx, 1.0f - Lettery));
        _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
        _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));
        
        _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
        _geometry->pushVertex(glm::vec3(x + space, y, 0));
        _geometry->pushVertex(glm::vec3(x + space + size, y, 0));
        _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
        _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));
        _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - (Lettery + 1.0f / 16.0f)));
    }
    _geometry->build(GL_STATIC_DRAW);
}
