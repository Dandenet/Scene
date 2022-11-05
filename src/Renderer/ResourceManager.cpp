#include <glad/glad.h>

#include <sstream>
#include <fstream>

#include "ResourceManager.h"
#include "ModelLoader.h"
#include "TextureLoader.h"

namespace Renderer {

ResourceManager& ResourceManager::GetResourceManager() noexcept
{
    static ResourceManager manager;
    return manager;
}

TexturePtrType ResourceManager::GetTexture(const std::string &path)
{
    auto it = m_Textures.find(path);
    if (it != m_Textures.end())
        return it->second;

    TextureLoader loader;
    auto texture = loader.Load(path.c_str());

    m_Textures.emplace(path, texture);

    return texture;
}

ModelPtrType ResourceManager::GetModel(const std::string &fPath)
{

    auto it = m_Models.find(fPath);
    if (it != m_Models.end())
        return it->second;

    ModelLoader loader;
    auto model = loader.LoadModel(fPath);

    m_Models.emplace(fPath, model);

    return model;
}

ShaderProgramPtrType ResourceManager::GetShaderProgram(const std::string& vsPath,
                                                       const std::string& fsPath)
{

    auto it = m_ShadersPrograms.find(std::make_pair(vsPath, fsPath));
    if (it != m_ShadersPrograms.end())
        return it->second;

    std::stringstream vss;
    std::stringstream fss;
    std::ifstream fvs(vsPath);
    std::ifstream ffs(fsPath);

    fvs.exceptions(fvs.failbit);
    ffs.exceptions(ffs.failbit);

    vss << fvs.rdbuf();
    fvs.close();

    fss << ffs.rdbuf();
    ffs.close();

    Shader vShader(GL_VERTEX_SHADER);
    vShader.Compile(vss.str().c_str());

    Shader fShader(GL_FRAGMENT_SHADER);
    fShader.Compile(fss.str().c_str());


    ShaderProgramPtrType shaderProgram = ShaderProgram::Create();
    shaderProgram->AddShader(vShader);
    shaderProgram->AddShader(fShader);
    shaderProgram->Link();

    m_ShadersPrograms.emplace(std::make_pair(vsPath, fsPath), shaderProgram);

    return shaderProgram;
}

};
