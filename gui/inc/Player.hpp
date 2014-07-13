
#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "IEntity.hpp"
# include "Model.hpp"
# include "Rectangle.hpp"

# define COMPARE(a, b) std::abs(a - b) < FLT_EPSILON

class Player : public IEntity
{
public:
    enum Status {
        ALIVE = 0,
        DYING,
        DEAD,
        SUMMONING
    };
    
public:
    Player();
    Player(const Player &player, const glm::vec2 &position, size_t nb, int lvl, const std::string &team);
    virtual ~Player();
    void	destroyModel();
    void update(const sf::Clock &clock, float speedOfServer);
    virtual void draw(Shader *shader) const;
    virtual void setRecourse(const std::list<int> &recourse);
    virtual const std::list<int> &getRecourse() const;
    virtual const glm::vec2 &getPosition() const;
    virtual void setPosition(const glm::vec2 &pos);
    const glm::vec3 &getModelPos() const;
    bool moveTo(const glm::vec2 &pos);
    size_t getNb() const;
    void setOrientation(size_t orientation);
    void setStatus(Status status);
    Status getStatus() const;
    void	setBroadcasting(bool broadcasting);
    bool	isBroadcasting() const;
    void	drawBroadcast(Shader *shader, const glm::vec3 &position, int winY);
    size_t getLvl() const;
    void setLvl(size_t lvl);
    const std::string &getTeam() const;
    void setTeam(const std::string &team);
    const glm::vec3 &getSphereCenter() const;
    float getSphereRadius() const;
    
    typedef std::list<glm::vec2> PosList;
    typedef std::list<glm::vec3> Way;
    
private:
    void updateSphereCenter();
    
private:
    Status _status;
    bool	_broadcasting;
    size_t _nb;
    glm::vec2 _position;
    glm::vec3 _sphereCenter;
    float _sphereRadius;
    Model *_clarkKent;
    Rectangle _broadcast;
    std::list<int> _recourse;
    size_t _lvl;
    float _distance;
    glm::vec2 _previousPos;
    std::string _team;
    PosList _posList;
    Way _way;
    std::list<size_t> _orientation;
};

#endif /* PLAYER_HPP_ */
