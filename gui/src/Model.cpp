#include <stdexcept>

#include "Model.hpp"

Model::Model() : AObject()
{
    _geometry = NULL;
    _texture = NULL;
}

Model::Model(const Model &model)
: AObject(), _geometry(model._geometry), _texture(model._texture)
{

}

Model::~Model()
{
    if (_texture != NULL)
        delete _texture;
}

void    Model::loadObj(const std::string &objPath, const std::string &texturePath)
{
    float x, y, z = 0;

    _geometry = new Geometry;

    _load = 0; //0% done

    std::cout << "loading OBJ file: " << objPath << "...";
    std::cout << "loading texture file: " << texturePath << "...";

    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;

    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> uvIndices;
    std::vector<unsigned int> normalIndices;


    std::ifstream file(objPath.c_str(), std::ios::in);

    if(!file)
        throw std::runtime_error(std::string("Can't open file ") + std::string(objPath));
    else
    {

        std::string line;

        _load = 2; //2% done

        // read the first word of the line
        while(getline(file,line)) // EOF = End Of File. Quit the loop.
        {
            if (line.substr(0,2) == "v ")
            {
                line = line.substr(2);
                std::istringstream iss(line);
                iss >> x >> y >> z;
                glm::vec3 vertex(x, y, z);
                out_vertices.push_back(vertex);
            }
            else if (line.substr(0, 3) == "vt ")
            {
                line = line.substr(3);
                std::istringstream iss(line);
                iss  >> x >> y;
                y = 1.0 - y; // <- to deal with the fact that opengl got is reference at down right corner
                glm::vec2 uv(x, y);
                out_uvs.push_back(uv);

            }

            else if (line.substr(0, 3) == "vn ")
            {
                line = line.substr(3);
                std::istringstream iss(line);
                iss >> x >> y >> z;
                glm::vec3 normal(x, y, z);
                out_normals.push_back(normal);
            }

            else if (line.substr(0, 2) == "f ")
            {
                line = line.substr(2);

                unsigned int vertexIndex[3]= {0}, uvIndex[3]= {0}, normalIndex[3] = {0};
                unsigned int* indice[3] = {vertexIndex, uvIndex, normalIndex};

                //Replace ' ' by '/'
                line[(line.find(' '))] = '/';
                line[(line.find(' ', line.find(' ')))] = '/';


                for(int i = 0; i < 9; i++)
                {
                    int first_slash = line.find('/');
                    std::istringstream iss(line.substr(0, first_slash));
                    iss >> ((indice[i % 3])[i / 3]);
                    ((indice[i % 3])[i / 3]) -= 1;
                    line = line.substr(first_slash + 1);
                }

                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }

        }
        _load = 15; //15% done

        std::vector<glm::vec3>      fin_vertices;
        std::vector<glm::vec3>      fin_uvs;
        std::vector<glm::vec3>      fin_normals;
        std::vector<unsigned int>   fin_Indices;

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            _load = 15 + ((i) / vertexIndices.size()) * 75;

            // Put the attributes in buffers
            glm::vec3 temp_vert;
            if ((vertexIndices[i]) < (out_vertices.size())) //To prevent overflow
            {
                temp_vert = out_vertices[vertexIndices[i]];
            }
            else
            {
                temp_vert = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            glm::vec2 temp_uvs;
            if ((uvIndices[i]) < (out_uvs.size())) //To prevent overflow
            {
                temp_uvs = out_uvs[uvIndices[i]];
            }
            else
            {
                temp_uvs = glm::vec2(0.0f, 0.0f);
            }

            glm::vec3 temp_norm;
            if ((normalIndices[i]) < (out_normals.size())) //To prevent overflow
            {
                temp_norm = out_normals[normalIndices[i]];
            }
            else
            {
                temp_norm = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            _geometry->pushVertex(temp_vert).pushUv(temp_uvs).pushNormal(temp_norm);
        }
        _texture = new sf::Texture;
        _texture->loadFromFile(texturePath);

        _load = 90; //90% done

        std::cout << std::endl;
        file.close();  // on ferme le file

        _geometry->build(GL_STATIC_DRAW);

        _load = 100; //100% done
    }
}

void    Model::draw(Shader *shader)
{
    sf::Texture::bind(_texture);
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}

void	Model::destroyGeometry()
{
    if (_geometry != NULL)
        delete _geometry;
}
