#ifndef SHADER_H
#define SHADER_H

#include <string>


namespace Renderer {

typedef unsigned int ShaderIdType;
typedef int ShaderType;

class Shader
{
public:
    Shader(ShaderType type);
    ~Shader();

    void Compile(const char* source);

private:
    ShaderIdType m_Id;

    friend class ShaderProgram;
};

} // namespace

#endif
