#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;

void main()
{
    // ambient light
    float ambientIntensity  = 0.1;
    vec3 ambient = ambientIntensity * lightColor;

    // diffues light
    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 norm = normalize(Normal);
    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * lightColor;

    // specular light
    float specularStrength = 0.5;
    int shininess = 32;
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

}