#include "objloader.hpp"

#include "../Utilities/maths/vector3d.h"


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

Objets* loadOBJ(const char* path,int texture,int* load)
{
    std::string final_texpath;

    if(load!=NULL)
        *load = 0; //0% done

    std::cout << "Loading OBJ file " << path << "...";

    std::vector<Vector3D> out_vertices;
    std::vector<Vector3D> out_uvs;
    std::vector<Vector3D> out_normals;

    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> uvIndices;
    std::vector<unsigned int> normalIndices;


    std::ifstream fichier(path, std::ios::in);  // on ouvre le fichier en lecture

    if(!fichier)
    {
        throw Erreur(std::string("Can't open file ")+std::string(path),-1);
    }
    else
    {

        std::string line;

        if(load!=NULL)
            *load = 2; //2% done

        // read the first word of the line
        while(getline(fichier,line)) // EOF = End Of File. Quit the loop.
        {
            //std::cout << ".";
            if (line.substr(0,2) == "v ")
            {
                line = line.substr(2);
                std::istringstream iss(line);
                Vector3D vertex;
                iss >> vertex.X >> vertex.Y >> vertex.Z;
                out_vertices.push_back(vertex);
            }
            else if (line.substr(0,3) == "vt ")
            {
                line = line.substr(3);
                std::istringstream iss(line);
                Vector3D uv;
                uv.Z = 0;
                iss  >> uv.X  >> uv.Y;
                uv.Y = 1.0 - uv.Y; // <- to deal with the fact that opengl got is reference at down right corner
                out_uvs.push_back(uv);

            }

            else if (line.substr(0,3) == "vn ")
            {
                line = line.substr(3);
                std::istringstream iss(line);
                Vector3D normal;
                iss >> normal.X >> normal.Y >> normal.Z;
                out_normals.push_back(normal);
            }

            else if (line.substr(0,2) == "f ")
            {
                line = line.substr(2);

                unsigned int vertexIndex[3]= {0}, uvIndex[3]= {0}, normalIndex[3]= {0};
                unsigned int* indice[3] = {vertexIndex,uvIndex,normalIndex};

                //Replace ' ' by '/'
                line[(line.find(' '))] = '/';
                line[(line.find(' ',line.find(' ')))] = '/';


                for(int i=0; i<9; i++)
                {
                    int first_slashe = line.find('/');
                    std::istringstream iss(line.substr(0,first_slashe));
                    iss >> ((indice[i%3])[i/3]);
                    ((indice[i%3])[i/3]) -= 1; //-<-- fuck obj which start index at 1
                    line = line.substr(first_slashe+1);
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
            else
            {
                //Unknow header
            }

        }

        if(load!=NULL)
            *load = 15; //15% done

        std::vector<Vector3D>  fin_vertices;
        std::vector<Vector3D>  fin_uvs;
        std::vector<Vector3D>  fin_normals;
        std::vector<unsigned int>  fin_Indices;

        // For each vertex of each triangle
        for(unsigned int i=0; i<vertexIndices.size(); i++ )
        {
            if(load!=NULL)
                *load = 15+((i)/vertexIndices.size())*75;

            // Put the attributes in buffers
            Vector3D temp_vert;
            if((vertexIndices[i])<(out_vertices.size())) //To prevent overflow
            {
                temp_vert = out_vertices[vertexIndices[i]];
            }
            else
            {
                temp_vert = Vector3D(0.0,0.0,0.0);
            }

            Vector3D temp_uvs;
            if((uvIndices[i])<(out_uvs.size())) //To prevent overflow
            {
                temp_uvs = out_uvs[uvIndices[i]];
            }
            else
            {
                temp_uvs = Vector3D(0.0,0.0,0.0);
            }

            Vector3D temp_norm;
            if((normalIndices[i])<(out_normals.size())) //To prevent overflow
            {
                temp_norm = out_normals[normalIndices[i]];
            }
            else
            {
                temp_norm = Vector3D(0.0,0.0,0.0);
            }


            //Make a new vertice only if it doesn't already exist:
            bool exist=false;
            unsigned int j=0;
            for(j=0; j<fin_vertices.size()/*=fin_normals.size()*/; j++)
            {
                if((temp_vert == fin_vertices[j])&&(temp_uvs == fin_uvs[j])&&(temp_norm == fin_normals[j]))
                {
                    exist = true;
                    break;
                }

            }

            if(exist)
            {
                fin_Indices.push_back(j);
            }
            else //we create a new vertice
            {

                fin_vertices.push_back(temp_vert);
                fin_uvs     .push_back(temp_uvs);
                fin_normals .push_back(temp_norm);
                fin_Indices.push_back(fin_vertices.size()-1);

            }

        }

        if(texture != NO_TEXTURE) //We load the texture
        {
            //objet_textureid = loadTexture(final_texpath);
        }

        if(load!=NULL)
            *load = 90; //0% done


        Objets* obj = new Objets(fin_vertices,fin_uvs,fin_normals,fin_Indices);

        std::cout << std::endl;
        fichier.close();  // on ferme le fichier

        if(load!=NULL)
            *load = 100; //100% done

        return obj;
    }
}


GLuint loadTexture(const char *texpath)
{
    GLuint texture_id;

    SDL_Surface* img=SDL_LoadBMP(texpath);

    if(!img)
    {
        throw Erreur(std::string("Error while loading texture file ")+std::string(texpath)+std::string(" with error ")+std::string(SDL_GetError()),-1);
    }

    /* init_resources */
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, // target
                 0,  // level, 0 = base, no minimap,
                 GL_RGB, // internalformat
                 img->w,  // width
                 img->h,  // height
                 0,  // border, always 0 in OpenGL ES
                 GL_BGR,  // format
                 GL_UNSIGNED_BYTE, // type
                 img->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(img);

    return texture_id;
}
