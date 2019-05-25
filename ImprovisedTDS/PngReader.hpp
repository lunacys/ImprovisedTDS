#pragma once
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <png.h>

#include "Texture2D.hpp"

#ifndef PNG_SIG_SIZE
#define PNG_SIG_SIZE 8
#endif

class PngReader
{
public:
	static Texture2D* ReadFromFile(const std::string& filePath);
	
private:
	static bool Validate(std::ifstream& source);
	static void ReadFromIfstreamExt(png_structp pngPtr, png_bytep data, png_size_t length);
};

inline Texture2D* PngReader::ReadFromFile(const std::string& filePath)
{
	std::cout << "> Reading PNG: " << filePath << "..." << std::endl;

	// Open png file and stream it as binary file
	std::ifstream pngDataFile(filePath, std::ios::binary);

	if (!pngDataFile.is_open())
		throw std::runtime_error("ERROR: Couldn't find the file specified: " + filePath);
	pngDataFile.exceptions(std::ios::badbit);

	// Firstly, we validate our stream with the validate function
	if (!Validate(pngDataFile))
		throw std::runtime_error("ERROR: Data is not valid PNG-data!");

	// The png read struct
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!pngPtr)
		throw std::runtime_error("ERROR: Couldn't initialize png read struct!");

	// The png info struct
	png_infop infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr)
	{
		png_destroy_read_struct(&pngPtr, png_infopp(nullptr), png_infopp(nullptr));
		throw std::runtime_error("ERROR: Couldn't initialize png info struct!");
	}

	// Error handling..
	png_bytep* rowPtrs = nullptr;
	unsigned char* data = nullptr;

	if (setjmp(png_jmpbuf(pngPtr)))
	{
		// An error occured, so clean up what we have allocated so far..
		png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp(nullptr));
		if (rowPtrs != nullptr) delete[] rowPtrs;
		if (data != nullptr) delete[] data;

		throw std::runtime_error("ERROR: An error occured while reading the PNG file!");
	}

	png_set_read_fn(pngPtr, png_voidp(&pngDataFile), ReadFromIfstreamExt);

	// Set the amount signature bytes we've already read:
	png_set_sig_bytes(pngPtr, PNG_SIG_SIZE);
	// Now call png_read_info with our pngPtr as image handle, and infoPtr to recieve the file info
	png_read_info(pngPtr, infoPtr);

	png_uint_32 imgWidth = png_get_image_width(pngPtr, infoPtr);
	png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);

	// Bits per CHANNEL! not per pixel!
	png_uint_32 bitdepth = png_get_bit_depth(pngPtr, infoPtr);
	// Number of channels
	png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
	// Color type (RGB, RGBA, Luminance, etc..)
	png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

	/*std::cout << "Width: " << imgWidth << std::endl;
	std::cout << "Height: " << imgHeight << std::endl;
	std::cout << "Bitdepth: " << bitdepth << std::endl;
	std::cout << "Channels: " << channels << std::endl;
	std::cout << "Color Type: " << color_type << std::endl;*/

	switch(color_type)
	{
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(pngPtr);
			// Don't forget to update the channel info
			channels = 3;
			break;
		case PNG_COLOR_TYPE_GRAY:
			png_set_expand_gray_1_2_4_to_8(pngPtr);
			// And the bitdepth info
			bitdepth = 8;
			break;
		case PNG_COLOR_TYPE_RGB:
			png_set_add_alpha(pngPtr, 0xFF, PNG_FILLER_AFTER);
			channels += 1;
			break;
	}
	// If the image has a transperancy convert it to a full Alpha channel
	if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(pngPtr);
		channels += 1;
	}

	// We don't support 16 bit precision.. so if the image has 16 bits per channel
	// round it down to 8
	if (bitdepth == 16)
		png_set_strip_16(pngPtr);

	// We should let png update the information structs with the transformation we requested
	png_read_update_info(pngPtr, infoPtr);

	// Here's one of the pointers we've defined in the error handler section
	// Array of row pointers, one for every row
	rowPtrs = new png_bytep[imgHeight];

	// Allocate a buffer with enough space
	// (Don't use the stack, these blocks get big easilly)
	// This pointer was also defined in the error handling section, so we can clean it up on error
	data = new unsigned char[imgWidth * imgHeight * bitdepth * channels / 8];
	// This is the length in bytes, of one row
	const unsigned int stride = imgWidth * bitdepth * channels / 8;

	// A little for-loop here to set all the row pointers to the starting
	// adresses for every row in the buffer
	for (size_t i = 0; i < imgHeight; ++i)
	{
		// Set the pointer to the data pointer + i times the row stride
		// Notice that the row order is reversed with q
		// This is how at least OpenGL expects it,
		// and how many other image loaders present the data
		png_uint_32 q = (imgHeight - i - 1) * stride;
		rowPtrs[i] = png_bytep(data) + q;
	}

	// And here it is! The actuall reading of the image
	// Read the imagedata and write it to the adresses pointed to
	// by rowptrs (in other words: our image databuffer)
	png_read_image(pngPtr, rowPtrs);

	/*for (size_t y = 0; y < imgHeight; y++)
	{
		png_byte* row = rowPtrs[y];
		for (size_t x = 0; x < imgWidth; x++)
		{
			png_byte* ptr = &(row[x * 4]);
			//std::cout << "[[Pixel at position {" << x << "," << y << "} has RGBA values: " 
			//	<< (int)ptr[0] << ", " << (int)ptr[1] << ", " << (int)ptr[2] << ", " << (int)ptr[3] << std::endl;
		}
	}*/

	//unsigned char* pngdata = reinterpret_cast<unsigned char*>(pngPtr);

	// Delete the row pointers array
	delete[] png_bytep(rowPtrs);
	// And don't forget to clean up the read and info structs
	png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp(nullptr));

	std::cout << "> End Reading PNG: " << filePath << "..." << std::endl;

	return new Texture2D(imgWidth, imgHeight, data);
}


inline bool PngReader::Validate(std::ifstream& source)
{
	// Allocate a buffer of 8 bytes, where we can put the file signature
	png_byte pngsig[PNG_SIG_SIZE];
	int isPng = 0;

	// Read the 8 bytes from the stream into the sig buffer
	source.read(reinterpret_cast<char*>(pngsig), PNG_SIG_SIZE);

	// Check if the read worked..
	if (!source.good()) return false;

	// Let libpng check the sig. If this function returns 0, everything is ok 
	isPng = png_sig_cmp(pngsig, 0, PNG_SIG_SIZE);
	return (isPng == 0);
}

inline void PngReader::ReadFromIfstreamExt(png_structp pngPtr, png_bytep data, png_size_t length)
{
	// Here we get our IO pointer back from the read struct
	// This is the parameter we passed to the png_set_read_fn() function
	png_voidp a = png_get_io_ptr(pngPtr);
	// Cast the pointer to std::ifstream* and read 'length' bytes into 'data'
	static_cast<std::ifstream*>(a)->read(reinterpret_cast<char*>(data), length);
}
