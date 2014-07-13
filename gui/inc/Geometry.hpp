
#ifndef GEOMETRY_HPP_
# define GEOMETRY_HPP_

# ifndef GL_GLEXT_PROTOTYPES
#  define GL_GLEXT_PROTOTYPES
# endif

# ifndef GLM_FORCE_RADIANS
#  define GLM_FORCE_RADIANS
# endif

# ifndef GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
# endif 

# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glext.h>
#  define GEN_VERTEX_ARRAY glGenVertexArraysAPPLE
#  define BIND_VERTEX_ARRAY glBindVertexArrayAPPLE
#  define DELETE_VERTEX_ARRAY glDeleteVertexArraysAPPLE
# else
#  include <GL/gl.h>
#  include <GL/glext.h>
#  define GEN_VERTEX_ARRAY glGenVertexArrays
#  define BIND_VERTEX_ARRAY glBindVertexArray
#  define DELETE_VERTEX_ARRAY glDeleteVertexArrays
# endif

# include <iostream>
# include <vector>
# include <glm/glm.hpp>
# include "Shader.hpp"

# define BUFFER_OFFSET(a) ((char*)NULL + (a)) // VBO macro

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
