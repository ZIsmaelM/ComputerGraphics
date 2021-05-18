#version 330 core
in vec3 LampColor;
out vec4 FragColor;

void main()
{
    vec3 foo = LampColor;
    FragColor = vec4(foo, 1.0); //vec4(1.0); // set all 4 vector values to 1.0
}
