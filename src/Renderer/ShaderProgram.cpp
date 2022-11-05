#include <glad/glad.h>
#include <exception>
#include <sstream>
#include <fstream>

#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
namespace Renderer {
//------------------------------------------------------------------
ShaderProgram::ShaderProgram() :
    m_Id(glCreateProgram()) {}

//------------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_Id);
}

//------------------------------------------------------------------
void ShaderProgram::Use() const
{
    glUseProgram(m_Id);
}

//------------------------------------------------------------------
void ShaderProgram::AddShader(const Shader &shader)
{
    glAttachShader(m_Id, shader.m_Id);
    m_Shaders.push_back(shader.m_Id);
}

//------------------------------------------------------------------
void ShaderProgram::Link()
{
    glLinkProgram(m_Id);

    GLint succes = false;
    glGetProgramiv(m_Id, GL_LINK_STATUS, &succes);
    if(!succes) {
        int lenght = 0;
        glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &lenght);

        std::string error(lenght, ' ');
        glGetProgramInfoLog(m_Id, lenght, &lenght, &error[0]);
        throw std::exception(error.c_str());
    }

    // detach shaders
    for(const auto &shader : m_Shaders)
    {
        glDetachShader(m_Id, shader);
    }
}

//------------------------------------------------------------------
void ShaderProgram::SetMat4(const glm::mat4 &mat, const UniformType &uniform) const
{
    auto location = glGetUniformLocation(m_Id, uniform.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::SetVec3(const glm::vec3 &vec, const UniformType &uniform) const
{

    auto location = glGetUniformLocation(m_Id, uniform.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void ShaderProgram::SetInt(int value, const UniformType &uniform) const
{
    auto location = glGetUniformLocation(m_Id, uniform.c_str());
    glUniform1i(location, value);
}

void ShaderProgram::SetFloat(float value, const UniformType &uniform) const
{
    auto location = glGetUniformLocation(m_Id, uniform.c_str());
    glUniform1f(location, value);
}

ShaderProgramPtrType ShaderProgram::Create()
{
    return ShaderProgramPtrType(new ShaderProgram());
}

ShaderProgramPtrType ShaderProgram::GetPtr()
{
    return shared_from_this();
}
} //namespace
