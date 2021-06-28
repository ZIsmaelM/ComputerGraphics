# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight(vec3 lightDirection, vec4 lightColor, vec3 normal, vec3 halfVector)
{
    float diffuseIntensity = max(dot(lightDirection, normal), 0.0);
    vec4 diffuseComponent = lightColor * diffuse * diffuseIntensity;
    float specularIntensity = max(dot(halfVector, normal), 0.0);
    vec4 specularComponent = lightColor * specular * pow(specularIntensity, shininess);

    return diffuseComponent + specularComponent;
}

void main (void) 
{       
    if (enablelighting) {       
        vec4 finalcolor = vec4(0.0, 0.0, 0.0, 1.0); 

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader
        mat3 normalMatrix = mat3(transpose(inverse(modelview)));
        vec3 newNormal = normalize(normalMatrix * mynormal);
        vec4 newVertex = modelview * myvertex;
        vec3 fragpos = newVertex.xyz / newVertex.w;

        vec4 aggregateLight = vec4(0.0, 0.0, 0.0, 1.0);
        vec3 eyePos = vec3(0.0);
        
        for (int i = 0; i < numused; i++) {
            
            vec3 viewDirection = normalize(eyePos - fragpos);

            // Directional Light
            if (lightposn[i].w == 0.0) {
                vec3 lightDirection = normalize(lightposn[i].xyz);
                vec3 halfVector = normalize(lightDirection + viewDirection);
                aggregateLight += ComputeLight(lightDirection, lightcolor[i], newNormal, halfVector);
            }
            // Point Light
            else {
                vec3 lightpos = lightposn[i].xyz / lightposn[i].w; // dehomoginize the pos
                vec3 lightDirection = normalize(lightpos - fragpos);
                vec3 halfVector = normalize(lightDirection + viewDirection);
                aggregateLight += ComputeLight(lightDirection, lightcolor[i], newNormal, halfVector);
            }
        }

        // Color all pixels black for now, remove this in your implementation!
        finalcolor = ambient + aggregateLight;

        fragColor = finalcolor;
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}
