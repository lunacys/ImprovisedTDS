#pragma once
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Texture2D.hpp"

#include <stb_image.h>

class PngReader
{
public:
	static Texture2D* ReadFromFile(const std::string& filePath);
};

inline Texture2D* PngReader::ReadFromFile(const std::string& filePath)
{
	std::cout << "> Reading PNG: " << filePath << "..." << std::endl;

	int x, y, n;
	unsigned char* data = stbi_load(filePath.c_str(), &x, &y, &n, STBI_rgb);

	if (!data || x == 0 || y == 0 || n == 0)
	{
		throw new std::runtime_error("Error while reading image: " + filePath);
	}

	std::cout << "> End Reading PNG: " << filePath << "..." << std::endl;


	// TODO: Check this!
	//stbi_image_free(data);

	return new Texture2D(x, y, n, data);
}
