
#include "Geometry.hpp"

Geometry::Geometry()
{
//    _vboID = 20;
//    _vaoID = 10;
}

Geometry::~Geometry()
{
    glDeleteBuffers(1, &_vboID);
    DELETE_VERTEX_ARRAY(1, &_vaoID);
}

Geometry    &Geometry::pushVertex(const glm::vec3 &vertex)
{
    _vertices.push_back(vertex.x);
    _vertices.push_back(vertex.y);
    _vertices.push_back(vertex.z);
    return (*this);
}

Geometry    &Geometry::pushUv(const glm::vec2 &uv)
{
    _UVs.push_back(uv.x);
    _UVs.push_back(uv.y);
    return (*this);
}

Geometry    &Geometry::pushNormal(const glm::vec3 &normal)
{
    _normals.push_back(normal.x);
    _normals.push_back(normal.y);
    _normals.push_back(normal.z);
    return (*this);
}

void    Geometry::draw(Shader *shader, const glm::mat4 &transformation, GLenum mode)
{
    BIND_VERTEX_ARRAY(_vaoID);
    
    shader->setUniform("model", transformation);
    glDrawArrays(mode, 0, _vertices.size() / 3);
    
    BIND_VERTEX_ARRAY(0);
}

void    Geometry::build(GLenum usage)
{
    int verticesBytes, UVBytes, normalsBytes = 0;
    
    verticesBytes = _vertices.size() * sizeof(float);
    UVBytes = _UVs.size() * sizeof(float);
    normalsBytes = _normals.size() * sizeof(float);
    
//    if(glIsVertexArray(_vaoID) == GL_TRUE)
//        glDeleteVertexArrays(1, &_vaoID);
//    
//    if(glIsBuffer(_vboID) == GL_TRUE)
//        glDeleteBuffers(1, &_vboID);
    
    glGenBuffers(1, &_vboID);
    GEN_VERTEX_ARRAY(1, &_vaoID);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    
    // VRAM allocation
    glBufferData(GL_ARRAY_BUFFER, verticesBytes + UVBytes + normalsBytes, NULL, usage);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesBytes, &_vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, verticesBytes, UVBytes, &_UVs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, verticesBytes + UVBytes, normalsBytes, &_normals[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    BIND_VERTEX_ARRAY(_vaoID);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    
    // Getting vertices from GPU
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    
    // Getting UVs from GPU
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(verticesBytes));
    glEnableVertexAttribArray(3);
    
    // Getting normals from GPU
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(verticesBytes + UVBytes));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    BIND_VERTEX_ARRAY(0);
}