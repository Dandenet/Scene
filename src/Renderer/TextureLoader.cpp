#include <stdexcept>

#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


namespace Renderer {

TextureLoader::TextureLoader()
{

}

TexturePtrType TextureLoader::Load(const char *name)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char *img = stbi_load(name, &width, &height, &channels, 0);
    if (!img) {
        throw std::runtime_error(std::string("Cannot load resource ") + name);
    }

    TexturePtrType texture = Texture::Create(img, channels, width, height);

    stbi_image_free(img);

    return texture;
}


}
