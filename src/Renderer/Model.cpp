#include "Model.h"


Renderer::ModelPtrType Renderer::Model::Create()
{
    return ModelPtrType(new Model);
}

void Renderer::Model::AddMesh(const MeshPtrType &mesh)
{
    m_Meshes.emplace_back(mesh);
}

void Renderer::Model::Draw(const ShaderProgramPtrType &shader) const
{
    shader->Use();
    shader->SetMat4(m_ScaleMat * m_TranslationMat * m_RotationMat, "u_model");
    for (const auto& mesh : m_Meshes) {
        mesh->Draw(shader);
    }
}

Renderer::Model::Model() :
    m_TranslationMat(1.0f),
    m_RotationMat(1.0f),
    m_ScaleMat(1.0f)
{}
