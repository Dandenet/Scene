#include <glad/glad.h>
#include "Mesh.h"

namespace Renderer {


Mesh::Mesh(size_t numIndeces, const unsigned int *indices,
           size_t numVertices, const Vertex *vertices) :
    m_NumIndeces(numIndeces),
    m_NumVertices(numVertices)
{
    m_pIndeces =  new unsigned int [m_NumIndeces];
    memcpy(m_pIndeces, indices, sizeof(unsigned int) * m_NumIndeces);

    m_pVertices = new Vertex [m_NumVertices];
    memcpy(m_pVertices, vertices, sizeof(Vertex) * m_NumVertices);
    Init();
}

Mesh::~Mesh()
{
    delete [] m_pIndeces;
    delete [] m_pVertices;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(const ShaderProgramPtrType &shader) const
{
    shader->Use();
    m_Material.Use(shader);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int)m_NumIndeces, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

MeshPtrType Mesh::Create(size_t numIndeces, const unsigned int *indices,
                         size_t numVertices, const Vertex *vertices)
{
    return MeshPtrType(new Mesh(numIndeces, indices, numVertices, vertices));
}

void Mesh::SetMaterial(const Material &material)
{
    m_Material = material;
}


void Mesh::Init()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_NumVertices, m_pVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndeces, m_pIndeces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, point));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

} //!namespace Renderer
