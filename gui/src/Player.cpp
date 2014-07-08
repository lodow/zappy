#include "Player.hpp"

Player::Player(const glm::vec2 &position) : _position(position), _clarkKent(new Model)
{
  _clarkKent->loadObj("res/models/superman/superman.obj", "res/models/superman/superman_d.png");
  _clarkKent->translate(glm::vec3(_position.x, 0.5, _position.y));

}

Player::Player(const Player &player)
{
  _clarkKent = new Model(*player._clarkKent);
  _position = player.getPosition();
  _clarkKent->translate(glm::vec3(_position.x, 0.5, _position.y));
}

Player::~Player()
{
  // TODO Auto-generated destructor stub
}

void Player::draw(Shader *shader)
{
  shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
  _clarkKent->draw(shader);
}

void Player::setRecourse(const std::list<int> &recourse)
{
  _recourse = recourse;
}

const glm::vec2 &Player::getPosition() const
{
  return _position;
}

void Player::setPosition(const glm::vec2 &pos)
{
  _position = pos;
}
