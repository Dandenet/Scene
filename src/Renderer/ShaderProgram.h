#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <memory>


namespace Renderer {

class ShaderProgram;

using ShaderProgramPtrType = std::shared_ptr<ShaderProgram>;


class ShaderProgram : public std::enable_shared_from_this<ShaderProgram> {
public:
    typedef std::string UniformType;

    ~ShaderProgram();

    void Use() const;
    void AddShader(const Shader &shader);
    void Link();

    void SetMat4(const glm::mat4 &mat, const UniformType &uniform) const;
    void SetVec3(const glm::vec3 &vec, const UniformType &uniform) const;
    void SetInt(int value, const UniformType &uniform) const;
    void SetFloat(float value, const UniformType &uniform) const;

    static ShaderProgramPtrType Create();
    ShaderProgramPtrType GetPtr();

private:
    ShaderIdType m_Id;
    std::vector<ShaderIdType> m_Shaders;

    ShaderProgram();
};
}; //namespace


#endif
