#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec3 TexCoord;

uniform mat4 PVM;
uniform mat4 model;

void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));
   Normal = mat3(transpose(inverse(model))) * aNormal;  

   gl_Position = PVM * vec4(aPos, 1.0f);
   TexCoord = aTexCoord;
}

