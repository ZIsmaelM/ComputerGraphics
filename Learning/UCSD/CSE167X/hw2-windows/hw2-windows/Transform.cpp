// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.

    // *** Copied from HW1 *** //
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

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    // *** Copied from HW1 *** //
    mat3 rotationMatrix = rotate(degrees, up);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.
    // *** Copied from HW1 *** //
    vec3 axisOfRotation = normalize(cross(eye, up)); // swapping eye and up changes the rotation direction
    mat3 rotationMatrix = rotate(degrees, axisOfRotation);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.
    // *** Copied from HW1 *** //
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);

    vec4 lookAtVecU = vec4(u.x, v.x, w.x, 0);
    vec4 lookAtVecV = vec4(u.y, v.y, w.y, 0);
    vec4 lookAtVecW = vec4(u.z, v.z, w.z, 0);
    vec4 lookAtVecH = vec4(-dot(u, eye), -dot(v, eye), -dot(w, eye), 1);
    mat4 lookAtMatrix = mat4(lookAtVecU, lookAtVecV, lookAtVecW, lookAtVecH);

    return lookAtMatrix;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.
    float d = cos(glm::radians(fovy / 2)) / sin(glm::radians(fovy / 2));
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2 * zFar * zNear) / (zFar - zNear);

    vec4 colA = vec4(d / aspect, 0, 0, 0);
    vec4 colB = vec4(0, d, 0, 0);
    vec4 colC = vec4(0, 0, A, -1);
    vec4 colD = vec4(0, 0, B, 0);
    mat4 projectionMatrix = mat4(colA, colB, colC, colD);

    return projectionMatrix;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    // YOUR CODE FOR HW2 HERE
    // Implement scaling
    vec4 colA = vec4(sx, 0, 0, 0);
    vec4 colB = vec4(0, sy, 0, 0);
    vec4 colC = vec4(0, 0, sz, 0);
    vec4 colD = vec4(0, 0, 0, 1);
    mat4 scaleMatrix = mat4(colA, colB, colC, colD);

    return scaleMatrix;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    vec4 colA = vec4(1, 0, 0, 0);
    vec4 colB = vec4(0, 1, 0, 0);
    vec4 colC = vec4(0, 0, 1, 0);
    vec4 colD = vec4(tx, ty, tz, 1);
    mat4 translationMatrix = mat4(colA, colB, colC, colD);

    return translationMatrix;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
