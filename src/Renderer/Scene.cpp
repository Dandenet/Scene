#include "Scene.h"

namespace Renderer {

Scene::Scene() {}

void Scene::AddModel(const ModelPtrType &model)
{
    m_Models.emplace_back(model);
}

void Scene::SetShader(const ShaderProgramPtrType &shader)
{
    m_Shader = shader;
}

void Scene::SetCamera(Camera* pCamera)
{
    m_Camera = pCamera;
}

void Scene::Update()
{
    m_Shader->Use();
    m_Shader->SetMat4(m_Camera->LookAt(), "u_view");
    for (auto& model : m_Models) {
        model->Draw(m_Shader);
    }
}

}
