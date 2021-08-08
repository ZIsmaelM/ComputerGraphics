#include "image.h"

Image::Image()
	: width_{ 600 }, height_{ 400 }, bytesPerRow_{ 600 * 3 }, bitsPerPixel_{ 24 }
{
}

Image::Image(int w, int h, int bytesPerRow, int bitsPerPixel)
	: width_{ w }, height_{ h }, bytesPerRow_{ bytesPerRow }, bitsPerPixel_{ bitsPerPixel }
{
	std::cout << "Creating Image" << std::endl;
}

Image::~Image(){}

void Image::SaveImage(std::string fname, uint8_t* pixels, int numSamples)
{
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width_, height_
		, bytesPerRow_, bitsPerPixel_, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, image, fname.c_str(), 0);
}
