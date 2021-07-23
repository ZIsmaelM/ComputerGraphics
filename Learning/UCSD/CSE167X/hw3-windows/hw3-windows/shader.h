#pragma once
#include <iostream>
#include "transform.h"

void ColorPixel(uint8_t* pixels, int index, Vector3 color)
{
	pixels[index] = (uint8_t)color.x_; // Blue
	pixels[index + 1] = (uint8_t)color.y_; // Green
	pixels[index + 2] = (uint8_t)color.z_; // Red
}