
#ifndef SHADER_HPP_
# define SHADER_HPP_

# ifndef GLM_FORCE_RADIANS
#  define GLM_FORCE_RADIANS
# endif

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
# else
#   ifndef GL_GLEXT_PROTOTYPES
#    define GL_GLEXT_PROTOTYPES
#   endif
#  include <GL/gl.h>
#  include <GL/glext.h>
# endif

# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <iostream>
# include <string>
# include <fstream>
# include <map>

class Shader
{
    
public:
    
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    Shader(const Shader &shader);
    ~Shader();
    
    void create();
    void deleteShader();
    
    void bind() const;
    
    bool setUniform(std::string const& name, GLint value) const;
    bool setUniform(std::string const& name, glm::vec3 const& vector) const;
    bool setUniform(std::string const& name, glm::vec4 const& vector) const;
    bool setUniform(std::string const& name, glm::mat4 const& matrix) const;
    
    GLuint getProgramID() const;
    Shader& operator=(Shader const &shader);
    
    int operator[](const std::string &uni_string); //Return the location of the associated uniform
    
private:
    
    void initialize(GLuint &shader, GLenum type, std::string const &source);
    void bindAttribLocation();
    void bindUniformMap();
    
    std::map<std::string, GLuint> _uniformMap;
    
    std::string _vertexSource;
    std::string _fragmentSource;
    
    GLuint _vertexID;
    GLuint _fragmentID;
    GLuint _programID;
    
    bool _initialise;
};


#endif
