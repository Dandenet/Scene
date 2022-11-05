#ifndef TEXTURE_H
#define TEXTURE_H
#include <memory>



namespace Renderer {

class Texture;
using TexturePtrType = std::shared_ptr<Texture>;

class Texture : public std::enable_shared_from_this<Texture>
{
    typedef unsigned int TextureType;
public:
    ~Texture();

    static TexturePtrType Create(const uint8_t* data, uint32_t colorModel,
                                 uint32_t width, uint32_t height);
    TexturePtrType GetPtr();

    void Use(uint32_t Number) const;
private:
    TextureType m_Id;

    const uint8_t* m_Data;
    uint32_t m_ColorModel;
    uint32_t m_Width, m_Height;

    void Init();
    Texture(const uint8_t* data, uint32_t colorModel,
            uint32_t width, uint32_t height);

    Texture(const Texture& other) = delete;
    Texture(Texture&& other) = delete;
};

}

#endif
