#include <glad/glad.h>
#include "Texture.h"

namespace Renderer {

Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}

TexturePtrType Texture::Create(const uint8_t *data, uint32_t colorModel,
                               uint32_t width, uint32_t height)
{
    return TexturePtrType(new Texture(data, colorModel, width, height));
}

TexturePtrType Texture::GetPtr()
{
    return shared_from_this();
}

Texture::Texture(const uint8_t *data, uint32_t colorModel,
                 uint32_t width, uint32_t height) :

    m_Data(data), m_ColorModel(colorModel),
    m_Width(width), m_Height(height)
{
    Init();
}



void Texture::Use(uint32_t number) const
{
   glBindTexture(GL_TEXTURE_2D, m_Id);
   glActiveTexture(GL_TEXTURE0 + number);
}

void Texture::Init()
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}

};
