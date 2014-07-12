
#include "utils.hpp"
#include "Player.hpp"

Player::Player() : _clarkKent(new Model)
{
    _clarkKent->loadObj("res/models/superman/superman.obj", "res/models/superman/superman_d.png");
}

Player::Player(const Player &player, const glm::vec2 &position, size_t nb, int lvl)
: _status(ALIVE), _nb(nb), _position(position), _lvl(lvl), _distance(0), _previousPos(position)
{
    _clarkKent = new Model(*player._clarkKent);
    _clarkKent->translate(glm::vec3(_position.x, 0.5, _position.y));
    _clarkKent->scale(glm::vec3(0.7, 0.7, 0.7));
    _way.push_back(glm::vec3(0, 0, -1));
    _way.push_back(glm::vec3(1, 0, 0));
    _way.push_back(glm::vec3(0, 0, 1));
    _way.push_back(glm::vec3(-1, 0, 0));
}

Player::~Player()
{
    
}

void	Player::destroyModel()
{
    _clarkKent->destroyGeometry();
}

void Player::setOrientation(size_t orientation)
{
    //    _orientation.push_back(orientation);
    //}
    //
    //void Player::update(UNUSED const sf::Clock &clock)
    //{
    //    if (!_posList.empty()) {
    //        Way::const_iterator it = _way.begin();
    //        for (size_t j = 0; j != _orientation.front() && j != 4; ++j) {
    //            ++it;
    //        }
    //        if (!_i) {
    //            _clarkKent->setRotation(glm::vec3(0, 0, 0));
    //            _clarkKent->rotate(glm::vec3(0, -1, 0), 90 * _orientation.front() + 180);
    //        }
    //        _clarkKent->translate(glm::vec3((*it).x * 0.05f, 0, (*it).z * 0.05f));
    //        ++_i;
    //        if (_i == 20) {
    //            if (std::abs(_position.x - _posList.front().x) > 1 + FLT_EPSILON) {
    //                float un = (_posList.front().x - _position.x) / std::abs(_posList.front().x - _position.x);
    //                _clarkKent->translate(glm::vec3(_posList.front().x - _position.x + un, 0, 0));
    //            }
    //            else if (std::abs(_position.y - _posList.front().y) > 1 + FLT_EPSILON) {
    //                float un = (_posList.front().y - _position.y) / std::abs(_posList.front().y - _position.y);
    //                _clarkKent->translate(glm::vec3(0, 0, _posList.front().y - _position.y + un));
    //            }
    //            _position = _posList.front();
    //            _posList.pop_front();
    //            _orientation.pop_front();
    //            _i = 0;
    //        }
    //    }
    //}
    //
    //void Player::draw(Shader *shader) const
    //{
    //    shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
    //    shader->setUniform("ambientLight", glm::vec4(0.02, 0.02, 0.02, 1));
    //    _clarkKent->draw(shader);
    //}
    //
    _orientation.push_back(orientation);
}

void Player::update(const sf::Clock &clock, float serverSpeed)
{
    if (!_posList.empty() && _status == Player::ALIVE) {
        Way::const_iterator it = _way.begin();
        for (size_t j = 0; j != 4 && j != _orientation.front(); ++j) {
            ++it;
        }
        if (!_distance) {
            _clarkKent->setRotation(glm::vec3(0, 0, 0));
            _clarkKent->rotate(glm::vec3(0, -1, 0), 90 * _orientation.front() + 180);
        }
        float distance = clock.getElapsedTime().asSeconds() * serverSpeed;
        
        if ((_distance + distance) > 1)
            distance = 1 - _distance;
        _clarkKent->translate(glm::vec3((*it).x * distance, 0, (*it).z * distance));
        _distance += distance;
        if (_distance > 1 || COMPARE(_distance, 1)) {
            if (std::abs(_position.x - _posList.front().x) > 1) {
                float un = (_posList.front().x - _position.x) / std::abs(_posList.front().x - _position.x);
                _clarkKent->translate(glm::vec3(_posList.front().x - _position.x + un, 0, 0));
            }
            else if (std::abs(_position.y - _posList.front().y) > 1) {
                float un = (_posList.front().y - _position.y) / std::abs(_posList.front().y - _position.y);
                _clarkKent->translate(glm::vec3(0, 0, _posList.front().y - _position.y + un));
            }
            _position = _posList.front();
            _posList.pop_front();
            _orientation.pop_front();
            _distance = 0;
        }
    }
    else if (_status == Player::DYING && _posList.empty()) {
        _clarkKent->translate(glm::vec3(0, 0.05f, 0));
        if (_distance > 6)
            _status = Player::DEAD;
        _distance += clock.getElapsedTime().asSeconds() * 10;
    }
}

void Player::draw(Shader *shader) const
{
    if (_status == Player::DYING && _posList.empty())
        shader->setUniform("gColor", glm::vec4(1, 1, 1, 0.5f));
    else
        shader->setUniform("gColor", glm::vec4(1, 1, 1, 1));
    _clarkKent->draw(shader);
}

void Player::setRecourse(const std::list<int> &recourse)
{
    _recourse = recourse;
}

const glm::mat4 &Player::getTransformation() const
{
    return (_clarkKent->getTransformation());
}

const std::list<int> &Player::getRecourse() const
{
    return _recourse;
}

const glm::vec2 &Player::getPosition() const
{
    return _position;
}

void Player::setPosition(const glm::vec2 &pos)
{
    _position = pos;
}

size_t Player::getNb() const
{
    return _nb;
}

bool Player::moveTo(const glm::vec2 &pos)
{
    if (pos != _previousPos) {
        _posList.push_back(pos);
        _previousPos = pos;
        return true;
    }
    return false;
}

const glm::vec3	&Player::getSphereCenter() const
{
    return (_sphereCenter);
}

const float		Player::getSphereRadius() const
{
    return (_sphereRadius);
}

void Player::setStatus(Status status)
{
    _status = status;
}

Player::Status Player::getStatus() const
{
    return _status;
}
