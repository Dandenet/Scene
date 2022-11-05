#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Model.h"

namespace Renderer {


class ResourceManager

{

public:
    static ResourceManager &GetResourceManager() noexcept;

    TexturePtrType   GetTexture(const std::string &path);
    ModelPtrType     GetModel(const std::string &path);

    ShaderProgramPtrType GetShaderProgram(const std::string& vsPath,
                                          const std::string& fsPath);

private:
    std::map<std::pair<std::string, std::string>, ShaderProgramPtrType> m_ShadersPrograms;
    std::map<std::string, TexturePtrType>                               m_Textures;
    std::map<std::string, ModelPtrType>                                 m_Models;

    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager(ResourceManager &&) = delete;

    ResourceManager&  operator= (const ResourceManager &) = delete;
    ResourceManager&& operator= (ResourceManager &&) = delete;
};

};

#endif
