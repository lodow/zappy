#ifndef DEF_SHADER
#define DEF_SHADER


// Includes

#ifdef WIN32
#include <GL/glew.h>

#elif __APPLE__
#include <OpenGL/gl3.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include "../Utilities/Erreur.h"

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#define BUFFER_OFFSET(a) ((char*)NULL + (a)) //Pour les VBO


class Shader
{

public:

    Shader(std::string vertexSource, std::string fragmentSource);
    Shader(Shader const &shader);
    ~Shader();

    void initialiser();
    void detruire();
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
