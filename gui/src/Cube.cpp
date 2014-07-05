
#include "Cube.hpp"

Cube::Cube()
: IEntity()
{
    _texture = NULL;
    _geometry = NULL;
}
Cube::Cube(const Cube &cube)
: IEntity(), _geometry(cube._geometry), _texture(cube._texture)
{
    
}

Cube::~Cube()
{
    
}

void    Cube::build()
{
    _geometry = new Geometry;
    
    glm::vec3 vertice[] = {
        glm::vec3(0.500000, -0.500000, -0.500000),
        glm::vec3(0.500000, -0.500000, 0.500000),
        glm::vec3(-0.500000, -0.500000, 0.500000),
        glm::vec3(-0.500000, -0.500000, -0.500000),
        glm::vec3(0.500000, 0.500000, -0.500000),
        glm::vec3(0.500000, 0.500000, 0.500000),
        glm::vec3(-0.500000, 0.500000, 0.500000),
        glm::vec3(-0.500000, 0.500000, -0.500000)
    };
    
    glm::vec2 uv[] = {
        glm::vec2(0.000000, 0.000000),
        glm::vec2(1.000000, 0.000000),
        glm::vec2(1.000000, 1.000000),
        glm::vec2(0.000000, 1.000000)
    };
    
    glm::vec3 normals[] = {
        glm::vec3(0.000000, 0.000000, -0.500000),
        glm::vec3(-0.500000, 0.000000, 0.000000),
        glm::vec3(0.000000, 0.000000, 0.500000),
        glm::vec3(0.000000, 0.000000, 0.500000),
        glm::vec3(0.500000, 0.000000, 0.000000),
        glm::vec3(0.500000, 0.000000, 0.000000),
        glm::vec3(0.000000, 0.500000, 0.000000),
        glm::vec3(0.000000, -0.500000, 0.000000)
    };
    
    _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
    _geometry->pushVertex(vertice[0]).pushUv(uv[1]).pushNormal(normals[0]);
    _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
    _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[0]);
    _geometry->pushVertex(vertice[3]).pushUv(uv[2]).pushNormal(normals[0]);
    _geometry->pushVertex(vertice[7]).pushUv(uv[3]).pushNormal(normals[0]);
    
    _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
    _geometry->pushVertex(vertice[6]).pushUv(uv[1]).pushNormal(normals[1]);
    _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
    _geometry->pushVertex(vertice[2]).pushUv(uv[0]).pushNormal(normals[1]);
    _geometry->pushVertex(vertice[7]).pushUv(uv[2]).pushNormal(normals[1]);
    _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[1]);
    
    _geometry->pushVertex(vertice[1]).pushUv(uv[0]).pushNormal(normals[2]);
    _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[2]);
    _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[2]);
    _geometry->pushVertex(vertice[5]).pushUv(uv[1]).pushNormal(normals[3]);
    _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[3]);
    _geometry->pushVertex(vertice[2]).pushUv(uv[3]).pushNormal(normals[3]);
    
    _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[4]);
    _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[4]);
    _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[4]);
    _geometry->pushVertex(vertice[4]).pushUv(uv[1]).pushNormal(normals[5]);
    _geometry->pushVertex(vertice[5]).pushUv(uv[2]).pushNormal(normals[5]);
    _geometry->pushVertex(vertice[1]).pushUv(uv[3]).pushNormal(normals[5]);
    
    _geometry->pushVertex(vertice[4]).pushUv(uv[0]).pushNormal(normals[6]);
    _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
    _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
    _geometry->pushVertex(vertice[7]).pushUv(uv[1]).pushNormal(normals[6]);
    _geometry->pushVertex(vertice[6]).pushUv(uv[2]).pushNormal(normals[6]);
    _geometry->pushVertex(vertice[5]).pushUv(uv[3]).pushNormal(normals[6]);
    
    _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
    _geometry->pushVertex(vertice[1]).pushUv(uv[1]).pushNormal(normals[7]);
    _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
    _geometry->pushVertex(vertice[0]).pushUv(uv[0]).pushNormal(normals[7]);
    _geometry->pushVertex(vertice[2]).pushUv(uv[2]).pushNormal(normals[7]);
    _geometry->pushVertex(vertice[3]).pushUv(uv[3]).pushNormal(normals[7]);

    _geometry->build(GL_STATIC_DRAW);    
}

void	Cube::destroyGeometry()
{
    delete _geometry;
}

bool    Cube::loadTexture(const std::string &path)
{
    if (_texture == NULL)
        _texture = new sf::Texture;
    _texture->loadFromFile(path);
    _texture->setSmooth(true);
//    _texture->setRepeated(true);
    return (true);
}

void    Cube::draw(Shader *shader)
{
    if (_texture != NULL)
        sf::Texture::bind(_texture);
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}
