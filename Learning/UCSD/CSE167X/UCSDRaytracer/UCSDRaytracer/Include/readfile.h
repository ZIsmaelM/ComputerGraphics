// Readfile definitions 
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <glew.h>
#include <freeglut.h>
#include "Transform.h"
#include "image.h"
#include "camera.h"
#include "hittablelist.h"
#include "shape.h"

using namespace std;

void matransform (stack<mat4> &transfstack, GLfloat * values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, GLfloat * values) ;
void readfile (const char * filename, Image& image, Camera& camera, HittableList& World) ;
