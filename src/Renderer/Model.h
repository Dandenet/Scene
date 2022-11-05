#ifndef RENDERER_MODEL_H
#define RENDERER_MODEL_H

#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"

namespace Renderer {

class Model;

using ModelPtrType = std::shared_ptr<Model>;

class Model : public std::enable_shared_from_this<Model>
{
public:
    static ModelPtrType Create();
    ModelPtrType GetPtr();

    void AddMesh(const MeshPtrType& mesh);
    void Draw(const ShaderProgramPtrType& shader) const;
private:
    glm::mat4 m_TranslationMat;
    glm::mat4 m_RotationMat;
    glm::mat4 m_ScaleMat;

    std::vector<MeshPtrType> m_Meshes;
    std::vector<TexturePtrType> m_Textures;

    Model();
};

};

#endif // RENDERER_MODEL_H
