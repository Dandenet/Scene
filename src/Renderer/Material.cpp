#include "Material.h"
#include "types.h"

namespace Renderer {

Material::Material(const glm::vec3& colorAmbient,
                   const glm::vec3& colorDiffuse,
                   const glm::vec3& colorSpecular) :
    m_ColorAmbient(colorAmbient),
    m_ColorDiffuse(colorDiffuse),
    m_ColorSpecular(colorSpecular) {}

void Material::AddTexture(const TexturePtrType& texture)
{
    m_Textures.emplace_back(texture);
}

void Material::Use(const ShaderProgramPtrType& shader) const
{
    shader->SetVec3(m_ColorAmbient, UniformAmbientColor);
    shader->SetVec3(m_ColorDiffuse, UniformDiffuseColor);
    shader->SetVec3(m_ColorSpecular, UniformSpecularColor);


    uint32_t i = 0;
    for (const auto& texture : m_Textures) {
        texture->Use(i);

        ++i;
    }
}


}
