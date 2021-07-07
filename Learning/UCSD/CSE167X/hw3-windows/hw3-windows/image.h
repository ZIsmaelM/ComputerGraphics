#pragma once

#include <iostream>
#include <FreeImage.h>

class Image
{
public:
	int width_;
	int height_;
	int bytesPerRow_;
	int bitsPerPixel_;

	Image();
	Image(int w, int h, int bytesPerRow, int bitsPerPixel);
	virtual ~Image();

	void SaveImage(std::string fname, uint8_t* pixels, int numSamples);

};