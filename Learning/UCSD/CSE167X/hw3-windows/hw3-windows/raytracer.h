#pragma once
#include <iostream>
#include "image.h"
#include "camera.h"

extern const int WIDTH;
extern const int HEIGHT;

uint8_t* Render(const int width, const int height, Camera camera)
{
	uint8_t* pixels = new uint8_t[width*height];
	return pixels;
}