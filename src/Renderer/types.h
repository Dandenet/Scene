#ifndef TYPES_H
#define TYPES_H
#include <glm/glm.hpp>

using Color3D = glm::vec3;
using Point3D = glm::vec3;
using Point2D = glm::vec2;


static constexpr const char* UniformAmbientColor = "u_material.ambient";
static constexpr const char* UniformDiffuseColor = "u_material.diffuse";
static constexpr const char* UniformSpecularColor = "u_material.specular";

#endif // TYPES_H
