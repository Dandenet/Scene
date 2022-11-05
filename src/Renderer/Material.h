#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include <list>

#include "Texture.h"
#include "ShaderProgram.h"

namespace Renderer {

static constexpr glm::vec3 DefaulAmbientColor = glm::vec3(0.0f, 0.0f, 0.0f);
static constexpr glm::vec3 DefaulDiffuseColor = glm::vec3(0.0f, 0.0f, 0.0f);
static constexpr glm::vec3 DefaulSpecularColor = glm::vec3(0.0f, 0.0f, 0.0f);


class Material
{
public:
    Material(const glm::vec3& colorAmbient = DefaulAmbientColor,
             const glm::vec3& colorDiffuse = DefaulDiffuseColor,
             const glm::vec3& colorSpecular = DefaulSpecularColor);


    void AddTexture(const TexturePtrType& texture);

    void Use(const ShaderProgramPtrType& shader) const;
private:
    glm::vec3 m_ColorAmbient;
    glm::vec3 m_ColorDiffuse;
    glm::vec3 m_ColorSpecular;

    std::list<TexturePtrType> m_Textures;

};

}

#endif // MATERIAL_H
