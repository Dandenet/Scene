#ifndef MESH_H
#define MESH_H
#include <memory>

#include "types.h"
#include "Material.h"
#include "ShaderProgram.h"

namespace Renderer {

class Mesh;
using  MeshPtrType = std::shared_ptr<Mesh>;

class Mesh : std::enable_shared_from_this<Mesh> {
    using BufObjType = unsigned int;

public:
    struct Vertex {
        Point3D point;
        Point3D normal;
        Point2D texCoord;
    };

    void Draw(const ShaderProgramPtrType& shader) const;

    static MeshPtrType Create(size_t numIndeces, const unsigned int* indices,
                              size_t numVertices, const Vertex* vertices);

    void SetMaterial(const Material& material);

    ~Mesh();
private:
    Mesh(size_t numIndeces, const unsigned int* indices,
         size_t numVertices, const Vertex* vertices);

    BufObjType          VBO, VAO, EBO;

    size_t              m_NumIndeces;
    unsigned int*       m_pIndeces;

    size_t              m_NumVertices;
    Vertex*             m_pVertices;

    Material            m_Material;

    void Init();
};

}; //!namespace Renderer

#endif
