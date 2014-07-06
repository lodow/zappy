
#ifndef GEM_HPP_
# define GEM_HPP_

# include <map>
# include "Model.hpp"

enum GEM_TYPE {
    
};

class Gem {

public:
    Gem();
    Gem(const Gem &gem);
    ~Gem();
    
    void draw(Shader *shader);
    
private:
    Model	*_model;
    std::map<COLOR, glm::vec4> _colorMap;
    std::map<GEM_TYPE, >
};

#endif