#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

void main()
{
    // ambient light
    vec3 ambient = light.ambient * material.ambient;

    // diffues light
    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 norm = normalize(Normal);
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diffuseStrength * material.diffuse);

    // specular light
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);


    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}