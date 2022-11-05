#ifndef SCENE_H
#define SCENE_H

#include <list>

#include "Model.h"
#include "Camera.h"
#include "ShaderProgram.h"


namespace Renderer {


class Scene
{
public:
    Scene();

    void Update();
    void AddModel(const ModelPtrType& model);
    void SetShader(const ShaderProgramPtrType& shader);

    void SetCamera(Camera *pCamera);

private:
    std::list<ModelPtrType> m_Models;
    ShaderProgramPtrType    m_Shader;
    Camera*                 m_Camera;
};

};
#endif
