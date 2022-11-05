#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTextureCoord;
layout (location = 2) in vec3 aNormal;


out vec3 color;
out vec2 textureCoord;
out vec3 Normal;
out vec3 fragPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(pos.xyz, 1.0);
    fragPos = vec3(model * vec4(pos, 1.0));
    textureCoord = aTextureCoord;
	Normal = vec3(model * vec4(aNormal, 1.0));
}
