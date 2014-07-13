#include <stdexcept>

#include "Shader.hpp"

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource)
: _vertexSource(vertexSource), _fragmentSource(fragmentSource), _vertexID(0), _fragmentID(0), _programID(0), _initialise(false)
{

}


Shader::Shader(Shader const &shader)
: _vertexSource(shader._vertexSource), _fragmentSource(shader._fragmentSource), _vertexID(0), _fragmentID(0), _programID(0), _initialise(shader._initialise)
{
    if(_initialise == true)
        create();
}


Shader::~Shader()
{
    deleteShader();
}


void Shader::create()
{
    //    Shaders creation
    initialize(_vertexID, GL_VERTEX_SHADER, _vertexSource);
    initialize(_fragmentID, GL_FRAGMENT_SHADER, _fragmentSource);

    //    Program creation
    _programID = glCreateProgram();

    glAttachShader(_programID, _vertexID);
    glAttachShader(_programID, _fragmentID);

    //    Program Linking
    bindAttribLocation();
    glLinkProgram(_programID);

    //    Check Linking state
    GLint link(0);
    glGetProgramiv(_programID, GL_LINK_STATUS, &link);

    if(link != GL_TRUE)
    {
        //        Getting error message length
        GLint length(0);
        char  *error(NULL);

        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &length);

        error = new char[length + 1];

        // Copie de l'erreur dans la chaine de caractères
        glGetProgramInfoLog(_programID, length, &length, error);
        error[length] = '\0';

        throw std::runtime_error(std::string("Shader file: ") + std::string(" failed to link: ") + std::string(error));

        delete[] error;
    }

    bindUniformMap();

    _initialise = true;
}


void Shader::initialize(GLuint &shader, GLenum type, const std::string &path)
{
    if (type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
        shader = glCreateShader(type);
    else
    {
        glDeleteShader(shader);
        throw std::runtime_error(std::string("Shader file: ") + path + std::string(" have a wrong type: "));
    }

    std::string src, srcLine;
    std::ifstream fileStream(path.c_str());

    if(!fileStream)
    {
        glDeleteShader(shader);
        throw std::runtime_error(std::string("Shader file: ") + path + std::string(" can't be opened: "));
    }

    while(getline(fileStream, srcLine))
    {
        src += srcLine + '\n';
    }

    fileStream.close();

    //    Shader compilation
    GLint shaderError(0), length(0);
    const GLchar* srcString = src.c_str();

    glShaderSource(shader, 1, &srcString, NULL);
    glCompileShader(shader);

    //    Compilation check
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderError);

    if(shaderError != GL_TRUE)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char *error = new char[length + 1];
        error[length] = '\0';

        glGetShaderInfoLog(shader, length, &length, error);

        throw std::runtime_error(std::string("Shader file: ") + path + std::string(" failed to compile: ") + std::string(error));

        delete[] error;
    }
}


void Shader::bindAttribLocation()
{
    glBindAttribLocation(_programID, 0, "vPosition");
    glBindAttribLocation(_programID, 1, "vColor");
    glBindAttribLocation(_programID, 2, "vNormal");
    glBindAttribLocation(_programID, 3, "vTexCoord");
}

void Shader::bindUniformMap()
{
    int uniformNb;
    int uniformStringLength;

    glGetProgramiv(_programID, GL_ACTIVE_UNIFORMS, &uniformNb);
    glGetProgramiv(_programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformStringLength);

    char* temp_buffer = new char[uniformStringLength + 1];


    for(int i = 0; i < uniformNb; i++)
    {
        unsigned int uniformType;
        int uniformID;
        int temp;

        glGetActiveUniform(_programID, i, uniformStringLength, NULL, &temp ,&uniformType, temp_buffer);
        uniformID = glGetUniformLocation(_programID, temp_buffer);
        _uniformMap[std::string(temp_buffer)] = uniformID;
    }

    delete[] temp_buffer;
}

bool Shader::setUniform(const std::string &name, GLint value) const
{
    glUniform1i(_uniformMap.find(name)->second, value);
    return (true);
}

bool Shader::setUniform(const std::string &name, const glm::vec3 &vector) const
{
    glUniform3fv(_uniformMap.find(name)->second, 1, glm::value_ptr(vector));
    return (true);
}

bool Shader::setUniform(const std::string &name, const glm::vec4 &vector) const
{
    glUniform4fv(_uniformMap.find(name)->second, 1, glm::value_ptr(vector));
    return (true);
}

bool Shader::setUniform(const std::string &name, const glm::mat4 &matrix) const
{
    glUniformMatrix4fv(_uniformMap.find(name)->second, 1, GL_FALSE, glm::value_ptr(matrix));

    return (true);
}



void Shader::bind() const
{
    glUseProgram(_programID);
}

int Shader::operator[](const std::string &uni_string)
{
    return _uniformMap[uni_string];
}


void Shader::deleteShader()
{
    glDeleteShader(_vertexID);
    glDeleteShader(_fragmentID);
    glDeleteProgram(_programID);

    _vertexID = 0;
    _fragmentID = 0;
    _programID = 0;
    _initialise = false;
}


Shader& Shader::operator=(Shader const &shader)
{
    if (this != &shader)
    {
        _vertexSource = shader._vertexSource;
        _fragmentSource = shader._fragmentSource;
        _initialise = shader._initialise;

        deleteShader();
        create();
    }
    return *this;
}


GLuint Shader::getProgramID() const
{
    return _programID;
}