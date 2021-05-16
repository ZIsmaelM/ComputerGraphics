#version 330 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient light
    float ambientIntensity  = 0.1f;
    vec3 ambient = ambientIntensity * lightColor;

    // diffues light
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);
    float diffuseStrength = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    // specular light
    float specularStrength = 0.5f;
    int shininess = 32;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), shininess);
    vec3 specular = spec * specularStrength * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

}