#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TexCoords;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    mat3 NormalMatrix = mat3(transpose(inverse(view * model)));
    Normal = NormalMatrix * aNormal;
    gl_Position = projection * vec4(FragPos, 1.0);
    LightPos = vec3(view * vec4(lightPos, 1.0));
    TexCoords = aTexCoords;
}