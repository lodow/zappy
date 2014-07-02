
#include "Shader.hpp"

Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexSource(vertexSource), m_fragmentSource(fragmentSource), m_vertexID(0), m_fragmentID(0), m_programID(0), m_initialise(false)
{

}


Shader::Shader(Shader const &shader) : m_vertexSource(shader.m_vertexSource), m_fragmentSource(shader.m_fragmentSource), m_vertexID(0), m_fragmentID(0), m_programID(0), m_initialise(shader.m_initialise)
{
    // On initialise le shader si le shader source est lui aussi initialisé
    if(m_initialise == true)
        initialiser();
}


Shader::~Shader()
{
    detruire();
}


void Shader::initialiser()
{
    // Création des shaders
    initialiserTypeShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource);
    initialiserTypeShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource);

    // Création du program
    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Linkage du program
    bindAttribLocation();
    glLinkProgram(m_programID);

    // On vérifie que le link c'est bien passé
    GLint link(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &link);

    if(link != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        char *erreur(NULL);

        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de l'erreur
        erreur = new char[tailleErreur + 1];

        // Copie de l'erreur dans la chaine de caractères
        glGetProgramInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        //Envoie de l'erreur
//        throw Erreur(std::string("Shader file: ") + std::string(" failed to link: ") + std::string(erreur), -1);
        std::cerr << std::string("Shader file: ") + std::string(" failed to link: ") + std::string(erreur) << std::endl;

        delete[] erreur;
    }

    bindUniformMap();

    m_initialise = true;
}


void Shader::initialiserTypeShader(GLuint &shader, GLenum type, std::string const &source)
{
    // Génération de l'objet OpenGL Shader
    if(type == GL_VERTEX_SHADER)
        shader = glCreateShader(type);

    else if(type == GL_FRAGMENT_SHADER)
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    else
    {
        glDeleteShader(shader);
//        throw Erreur(std::string("Shader file: ") + source + std::string(" have a wrong type "), -1);
        std::cerr << std::string("Shader file: ") + source + std::string(" have a wrong type ") << std::endl;
    }

    // Ouverture du fichier source
    std::string codeSource, ligneCodeSource;
    std::ifstream fichierSource(source.c_str());

    // On test l'ouverture du fichier
    if(!fichierSource)
    {
        glDeleteShader(shader);
//        throw Erreur(std::string("Shader file: ") + source+std::string(" can't be open "), -1);
        std::cerr << std::string("Shader file: ") + source+std::string(" can't be open ") << std::endl;
    }

    // Si le fichier existe et qu'il est ouvert, alors on peut lire son contenu
    while(getline(fichierSource, ligneCodeSource))
    {
        codeSource += ligneCodeSource + '\n';
    }

    fichierSource.close();

    // Compilation du shader
    GLint erreurCompilation(0), tailleErreur(0);
    const GLchar* chaineCodeSource = codeSource.c_str();

    glShaderSource(shader, 1, &chaineCodeSource, NULL);
    glCompileShader(shader);

    // Vérification de la compilation
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

    if(erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation d'une chaine de caractères
        char *erreur = new char[tailleErreur + 1];
        erreur[tailleErreur] = '\0';

        // Récupération de l'erreur
        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);


        //Envoie de l'erreur
//        throw Erreur(std::string("Shader file: ") + source + std::string(" failed to compile: ") + std::string(erreur), -1);
        std::cerr << std::string("Shader file: ") + source + std::string(" failed to compile: ") + std::string(erreur) << std::endl;

        // On libère la mémoire
        delete[] erreur;
    }
}


void Shader::bindAttribLocation()
{
    // Verrouillage des entrées Shader

    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");
    glBindAttribLocation(m_programID, 3, "in_Normal");
    glBindAttribLocation(m_programID, 4, "in_Tangent");
}

void Shader::bindUniformMap()
{
    //On recupere des valeurs utile
    int nb_uniform;
    int uniform_string_lenght;

    glGetProgramiv(m_programID,GL_ACTIVE_UNIFORMS, &nb_uniform);
    glGetProgramiv(m_programID,GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniform_string_lenght);

    char* temp_buffer = new char[uniform_string_lenght+1]; //on alloue un tableau de bonne taille


    for(int i=0;i<nb_uniform;i++) //pour chaque uniform on le met son id et sa string dans la map
    {
        unsigned int uniform_type;
        int uniform_id;
        int tempint;

        glGetActiveUniform(m_programID,i,uniform_string_lenght,NULL,&tempint,&uniform_type,temp_buffer);
        uniform_id = glGetUniformLocation(m_programID,temp_buffer);
        m_uniformMap[std::string(temp_buffer)]=uniform_id;
    }

    delete[] temp_buffer;
}

int Shader::operator[](std::string uni_string)
{
    return m_uniformMap[uni_string];
}


void Shader::detruire()
{
    // Destruction des objets OpenGL

    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);


    // RAZ des valeurs

    m_vertexID = 0;
    m_fragmentID = 0;
    m_programID = 0;
    m_initialise = false;
}


Shader& Shader::operator=(Shader const &shader)
{
    // Si le shader à copier n'est pas lui-même

    if(this != &shader)
    {
        // Copie des sources

        m_vertexSource = shader.m_vertexSource;
        m_fragmentSource = shader.m_fragmentSource;
        m_initialise = shader.m_initialise;


        // Destruction du shader actuel

        detruire();


        // Initialisation du nouveau shader

        initialiser();
    }

    return *this;
}


GLuint Shader::getProgramID() const
{
    return m_programID;
}

#include "../Utilities/DebugNewOff.h"
