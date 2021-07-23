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
	// TODO maybe pass in the pixels array instead?
	//int numSamples = width_ * height_;
	//uint8_t* pixels = new uint8_t[3 * numSamples];

	// populate pixels array with ray-traced
	//for (int i = 0; i < numSamples*3; i += 3)
	//{
	//	pixels[i] = 0xFF; // Blue
	//	pixels[i+1] = 0x00; // Green
	//	pixels[i+2] = 0x00; // Red
	//}

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width_, height_
		, bytesPerRow_, bitsPerPixel_, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, image, fname.c_str(), 0);
}
