#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>

#include <assimp/Importer.hpp>

#include "Model.h"

namespace  Renderer {


class ModelLoader
{

public:
    ModelPtrType LoadModel(const std::string& path);

private:
    Assimp::Importer m_Importer;
};

};

#endif // MODELLOADER_H
