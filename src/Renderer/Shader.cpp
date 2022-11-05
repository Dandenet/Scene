#include "Shader.h"
#include <glad/glad.h>
#include <stdexcept>
namespace Renderer {

Shader::Shader(ShaderType type) :
    m_Id(glCreateShader(type)) {}


Shader::~Shader()
{
    glDeleteShader(m_Id);
}

void Shader::Compile(const char *source)
{
    glShaderSource(m_Id, 1, &source, nullptr);
    glCompileShader(m_Id);

    GLint succes = false;
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &succes);

    if(!succes) {
        int logsize;
        glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &logsize);

        std::string error(logsize, '\0');
        glGetShaderInfoLog(m_Id, logsize, &logsize, &error[0]);

        glDeleteShader(m_Id);
        throw std::runtime_error(error.c_str());
    }
}

} //namespace
