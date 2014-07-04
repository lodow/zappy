
#ifndef GEOMETRY_HPP_
# define GEOMETRY_HPP_

# include <iostream>
# include <vector>
# include <glm/glm.hpp>
# include "Shader.hpp"

class Geometry {
public:
    Geometry();
    virtual ~Geometry();
    
    Geometry    &pushVertex(const glm::vec3 &);
    Geometry    &pushUv(const glm::vec2 &);
    Geometry    &pushNormal(const glm::vec3 &);
    
    void        draw(Shader *shader, const glm::mat4 &transformation, GLenum mode);
    void        build(GLenum usage);
    
protected:
    GLuint             _vboID;
    GLuint             _vaoID;
    
    std::vector<float> _vertices;
    std::vector<float> _UVs;
    std::vector<float> _normals;
};

#endif
