// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

void Transform::printMatrix(mat4 m) {
    // Column major
    printf("--MATRIX--\n");
    printf("%f %f %f %f\n", m[0][0], m[1][0], m[2][0], m[3][0]);
    printf("%f %f %f %f\n", m[0][1], m[1][1], m[2][1], m[3][1]);
    printf("%f %f %f %f\n", m[0][2], m[1][2], m[2][2], m[3][2]);
    printf("%f %f %f %f\n", m[0][3], m[1][3], m[2][3], m[3][3]);
}

void Transform::printMatrix(mat3 m) {
    // Column major
    printf("--MATRIX--\n");
    printf("%f %f %f\n", m[0][0], m[1][0], m[2][0]);
    printf("%f %f %f\n", m[0][1], m[1][1], m[2][1]);
    printf("%f %f %f\n", m[0][2], m[1][2], m[2][2]);
}

void printVector(vec3 v) {
    printf("--VECTOR--\n");
    printf("%f %f %f\n", v[0], v[1], v[2]);
}

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
    // YOUR CODE FOR HW1 HERE
    
    // Rodrigues rotation formula
    // Rotation matrix R = cos(angle)*I + sin(angle)*K + (1-cos(angle))*(K*transpose(K))
    // K is the cross-product matrix of the given axis

    // REMEMBER: OpenGL uses column major, not row major
    // create the cross-product matrix
    vec3 cp1 = vec3(0, axis.z, -axis.y);
    vec3 cp2 = vec3(-axis.z, 0, axis.x);
    vec3 cp3 = vec3(axis.y, -axis.x, 0);

    mat3 crossProductMatrix = mat3(cp1, cp2, cp3);

    // create the outer product matrix
    vec3 op1 = vec3(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z);
    vec3 op2 = vec3(axis.x * axis.y, axis.y * axis.y, axis.y * axis.z);
    vec3 op3 = vec3(axis.x * axis.z, axis.y * axis.z, axis.z * axis.z);
    mat3 outerProductMatrix = mat3(op1, op2, op3);

    mat3 identityMatrix(1.0);
    mat3 A = sin(glm::radians(degrees)) * crossProductMatrix;
    mat3 B = (1 - cos(glm::radians(degrees))) * outerProductMatrix;

    // wikipedia rotation matrix

    mat3 result = cos(glm::radians(degrees)) * identityMatrix + B + A;
    result[0] = normalize(result[0]);
    result[1] = normalize(result[1]);
    result[2] = normalize(result[2]);
    
    return result;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE

    mat3 rotationMatrix = rotate(degrees, up);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE

    vec3 axisOfRotation = normalize(cross(eye, up)); // swapping eye and up changes the rotation direction
    mat3 rotationMatrix = rotate(degrees, axisOfRotation);

    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up,w));
    vec3 v = glm::cross(w,u);

    vec4 lookAtVecU = vec4(u.x, v.x, w.x, 0);
    vec4 lookAtVecV = vec4(u.y, v.y, w.y, 0);
    vec4 lookAtVecW = vec4(u.z, v.z, w.z, 0);
    vec4 lookAtVecH = vec4(-dot(u, eye), -dot(v, eye), -dot(w, eye), 1);
    mat4 lookAtMatrix = mat4(lookAtVecU, lookAtVecV, lookAtVecW, lookAtVecH);
    
    //printf("LookAt A:\n");
    printMatrix(lookAtMatrix);

    return lookAtMatrix;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}