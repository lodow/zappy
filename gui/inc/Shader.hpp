
#ifndef SHADER_HPP_
# define SHADER_HPP_

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

#define BUFFER_OFFSET(a) ((char*)NULL + (a)) // VBO

class Shader
{

public:

    Shader(std::string vertexSource, std::string fragmentSource);
    Shader(Shader const &shader);
    ~Shader();

    void initialiser();
    void detruire();
    
    void bind() const;
    
    bool setUniform(std::string const& name, glm::vec3 const& vector) const;
    bool setUniform(std::string const& name, glm::mat4 const& matrix) const;
    
    GLuint getProgramID() const;
    Shader& operator=(Shader const &shader);

    int operator[](std::string uni_string); //Return the location of the associated uniform

private:

    void initialiserTypeShader(GLuint &shader, GLenum type, std::string const &source);
    void bindAttribLocation();
    void bindUniformMap();

    std::map<std::string,GLuint> m_uniformMap;

    std::string m_vertexSource;
    std::string m_fragmentSource;

    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    bool m_initialise;
};


#endif
