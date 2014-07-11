#include <Ground.hpp>

Ground::Ground(const glm::vec2 &pos, const Gem &gem) : _gem(gem), _position(pos)
{
    _sphereCenter.x = pos.x;
    _sphereCenter.y = 0.5f;
    _sphereCenter.z = pos.y;
    _sphereRadius = 0.5f;

    for (int i = 0; i < 6; ++i) {
        _gemList.push_back(new Gem(_gem, static_cast<GemType>(i), _position));
    }
}

Ground::~Ground()
{
    
}

void    Ground::draw(Shader *shader)
{
    std::list<int>::const_iterator rec = _recourse.begin();
    ++rec;
    for (GemList::const_iterator it = _gemList.begin(), end = _gemList.end(); it != end; ++it) {
        if (*rec)
            (*it)->draw(shader);
        ++rec;
    }
}

void Ground::setRecourse(const std::list<int> &recourse)
{
    _recourse = recourse;
}

const glm::mat4 &Ground::getTransformation() const
{
    return (_gem.getTransformation());
}

const glm::vec2 &Ground::getPosition() const {
    return _position;
}

void Ground::setPosition(const glm::vec2 &pos) {
    _position = pos;
}

const GemList &Ground::getGemList() const
{
    return (_gemList);
}

const glm::vec3	&Ground::getSphereCenter() const
{
    return (_sphereCenter);
}

const float		Ground::getSphereRadius() const
{
    return (_sphereRadius);
}