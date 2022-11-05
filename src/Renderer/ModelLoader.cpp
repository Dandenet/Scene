#include <stdexcept>
#include <iostream>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include "Material.h"
#include "ModelLoader.h"
#include "ResourceManager.h"

namespace Renderer {

ModelPtrType ModelLoader::LoadModel(const std::string &path)
{
    ResourceManager& manager = ResourceManager::GetResourceManager();


    auto scene = m_Importer.ReadFile(path, aiProcess_MakeLeftHanded |
                                     aiProcess_FlipWindingOrder |
                                     aiProcess_FlipUVs |
                                     aiProcess_PreTransformVertices |
                                     aiProcess_CalcTangentSpace |
                                     aiProcess_GenSmoothNormals |
                                     aiProcess_Triangulate |
                                     aiProcess_FixInfacingNormals |
                                     aiProcess_FindInvalidData |
                                     aiProcess_ValidateDataStructure);
    if (!scene)
        throw std::runtime_error(m_Importer.GetErrorString());


    ModelPtrType model = Model::Create();


    uint32_t numMeshes = scene->mNumMeshes;
    for (uint32_t i = 0; i < numMeshes; ++i) {


        // ============== load material ===================
        auto mesh = scene->mMeshes[i];
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D ambient (0.f,0.f,0.f);
        material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);

        aiColor3D diffuse (0.f,0.f,0.f);
        material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);

        aiColor3D specular (0.f,0.f,0.f);
        material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

        Material mat(glm::vec3(ambient.r, ambient.g, ambient.b),
                     glm::vec3(diffuse.r, diffuse.g, diffuse.b),
                     glm::vec3(specular.r, specular.g, specular.b));


        // ============== load texture pathes ===================
        static const aiTextureType types[] = {
            aiTextureType_NONE,
            aiTextureType_DIFFUSE,
            aiTextureType_SPECULAR,
            aiTextureType_AMBIENT,
            aiTextureType_EMISSIVE,
            aiTextureType_HEIGHT,
            aiTextureType_NORMALS,
            aiTextureType_SHININESS,
            aiTextureType_OPACITY,
            aiTextureType_DISPLACEMENT,
            aiTextureType_LIGHTMAP,
            aiTextureType_REFLECTION,
            aiTextureType_UNKNOWN
        };

        aiString name;
        for(unsigned int type = 0; type < sizeof(types) / sizeof(types[0]); ++type) {
            for(unsigned int idx = 0; AI_SUCCESS== material->Get(AI_MATKEY_TEXTURE(types[type],idx), name); ++idx) {
                size_t index = path.find_last_of("\\/");
                std::string texturePath = path.substr(0, index + 1) + name.C_Str();

                TexturePtrType texture = manager.GetTexture(texturePath);
                mat.AddTexture(texture);
            }
        }

        // ============== load mesh ==============================
        std::vector<Mesh::Vertex> vertices(mesh->mNumVertices);
        for (uint32_t j = 0; j < mesh->mNumVertices; ++j) {

            auto point = mesh->mVertices[j];
            vertices[j].point.x = point.x;
            vertices[j].point.y = point.y;
            vertices[j].point.z = point.z;


            if (mesh->HasNormals()) {
                auto normal = mesh->mNormals[j];
                vertices[j].normal.x = normal.x;
                vertices[j].normal.y = normal.y;
                vertices[j].normal.z = normal.z;
            }

            if (mesh->HasTextureCoords(0)) {
                auto texCoord = mesh->mTextureCoords[0][j];
                vertices[j].texCoord.x = texCoord.x;
                vertices[j].texCoord.y = texCoord.y;
            }
        }

        std::vector<unsigned int> indeces;

        for (uint32_t j = 0; j < mesh->mNumFaces; ++j) {
            auto face = mesh->mFaces[j];

            for (uint32_t k = 0; k < face.mNumIndices; ++k)
                indeces.push_back(face.mIndices[k]);
        }

        auto meshptr = Mesh::Create(indeces.size(), indeces.data(),
                                        vertices.size(), vertices.data());

        meshptr->SetMaterial(mat);

        model->AddMesh(meshptr);
    }


    return model;
}

};
