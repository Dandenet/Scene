#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include "Texture.h"

namespace Renderer {


class TextureLoader
{
public:
    TextureLoader();

    TexturePtrType Load(const char* name);
};

}

#endif // TEXTURELOADER_H
