
#include "SkyBox.hpp"

SkyBox::SkyBox()
{
    _cube = new Cube6Face;
    _cube->build();
    _cube->scale(glm::vec3(2));
    _cube->loadTexture("res/textures/skybox.png");
}

SkyBox::~SkyBox()
{
    delete _cube;
}

//void SkyBox::update(gdl::Clock const &clock)
//{
//    _cube->rotate(glm::vec3(1, 1, 0.6), 1.2f * clock.getElapsed());
//}

void SkyBox::draw(Shader *shader, const glm::vec3 &position)
{
    _cube->setPosition(position);
    _cube->rotate(glm::vec3(0, 1, 0), 0.01f);

    glDisable(GL_DEPTH_TEST);
    _cube->draw(shader);
    glEnable(GL_DEPTH_TEST);
}
