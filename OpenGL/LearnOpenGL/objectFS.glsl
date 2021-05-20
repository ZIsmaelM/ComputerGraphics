#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;
in vec2 TexCoords;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main()
{
    // ambient light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffues light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular light
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));


    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}