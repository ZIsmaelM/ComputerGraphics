/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  
  

// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 
  
/*****************************************************************************/

// Basic includes to get this file to work.

using namespace std;
#include "globals.h" 
#include "readfile.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, GLfloat* values) 
{
    mat4 transform = transfstack.top(); 
    vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
    vec4 newval = transform * valvec; 
    for (int i = 0; i < 4; i++) values[i] = newval[i]; 
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
    mat4 &T = transfstack.top(); 
    T = T * M; 
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.
string cmd;
bool readvals(stringstream &s, const int numvals, GLfloat* values) 
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i]; 
        if (s.fail()) {
            cout << "Failed reading value " << i << " for command " << cmd << ". will skip\n";
            return false;
        }
    }
    return true; 
}


void readfile(const char* filename, Image& image, Camera& camera, HittableList& world) 
{
    string str;// , cmd;
    ifstream in;
    in.open(filename);
    std::cout << "Opening file: " << filename << std::endl;
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        stack <mat4> transfstack; 
        transfstack.push(mat4(1.0));  // identity
        
        Material material;
        int maxVertices = 0;
        int vertexCount = 0;
        vector<vec3> vertices;

        getline (in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd; 
                int i;
                GLfloat values[10]; // Position and color for light, colors for others
                                    // Up to 10 params for cameras.  
                bool validinput; // Validity of input 

                if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        image.width = (int)values[0];
                        image.height = (int)values[1];
                        image.aspectRatio = image.width / (float)image.height;

                        delete[] image.pixels;
                        image.pixels = new uint8_t[3 * image.width * image.height];
                    }
                }
                else if (cmd == "output") {
                    if (s.fail()) {
                        cout << "Failed reading output file name. Saving as test.png." << endl;
                    }
                    else {
                        s >> image.name;
                    }
                }
                else if (cmd == "camera") {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {
                        camera = Camera(
                            glm::vec3(values[0], values[1], values[2]),
                            glm::vec3(values[3], values[4], values[5]),
                            glm::vec3(values[6], values[7], values[8]),
                            values[9],
                            image.aspectRatio);
                    }
                }
                                
                // Material Commands 
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in 
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors. 

                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            material.ambient[i] = values[i]; 
                        }
                    }
                } else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            material.diffuse[i] = values[i];
                        }
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            material.specular[i] = values[i];
                        }
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            material.emission[i] = values[i];
                        }
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values); 
                    if (validinput) {
                        material.shininess = values[0]; 
                    }
                } 

                // I've left the code for loading objects in the skeleton, so 
                // you can get a sense of how this works.  
                // Also look at demo.txt to get a sense of why things are done this way.
                else if (cmd == "sphere") {   
                    validinput = readvals(s, 4, values); 
                    if (validinput) {                      
                        vec3 center(values[0], values[1], values[2]);
                        float radius = values[3];

                        // TODO: figure out transforms
                        mat4 transform = transfstack.top();

                        Sphere sphere(center, radius, material, transform);
                        world.add(make_shared<Sphere>(sphere));
                    }
                }

                else if (cmd == "translate") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {
                        mat4 translationMatrix = Transform::translate(values[0], values[1], values[2]);
                        rightmultiply(translationMatrix, transfstack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {
                        mat4 scaleMatrix = Transform::scale(values[0], values[1], values[2]);
                        rightmultiply(scaleMatrix, transfstack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values); 
                    if (validinput) {
                        mat4 rotationMatrix = Transform::rotate(values[3], vec3(values[0], values[1], values[2]));
                        rightmultiply(rotationMatrix, transfstack);
                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top()); 
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n"; 
                    } else {
                        transfstack.pop(); 
                    }
                }

                //else if (cmd == "maxDepth") {}
                //else if (cmd == "directional") {}
                else if (cmd == "point") {}
                //else if (cmd == "attenuation") {}
                else if (cmd == "maxverts") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxVertices = values[0];
                    }
                }
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (validinput && vertexCount < maxVertices) {
                        vertices.push_back(vec3(values[0], values[1], values[2]));
                        vertexCount++;
                    }
                }
                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        vec3 vectorA = vertices[values[0]];
                        vec3 vectorB = vertices[values[1]];
                        vec3 vectorC = vertices[values[2]];

                        // TODO: figure out transforms
                        mat4 transform = transfstack.top();

                        Triangle tri(vectorA, vectorB, vectorC, material, transform);
                        world.add(make_shared<Triangle>(tri));
                    }
                }

                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n"; 
                }
            }
            getline (in, str); 
        }

        // Set up initial position for eye, up and amount
        // As well as booleans 

        //eye = eyeinit; 
        //up = upinit; 
        //amount = 0.01;
        //sx = sy = 1.0;  // keyboard controlled scales in x and y 
        //tx = ty = 0.0;  // keyboard controllled translation in x and y  
        //useGlu = false; // don't use the glu perspective/lookat fns
        //
        //glEnable(GL_DEPTH_TEST);
    } else {
        cerr << "Unable to Open Input Data File " << filename << "\n"; 
        throw 2; 
    }
}
