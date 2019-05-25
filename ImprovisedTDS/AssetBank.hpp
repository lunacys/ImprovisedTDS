#pragma once
#include "Texture2D.hpp"
#include "PngReader.hpp"

class AssetBank
{
public:
	static void CleanUp();
	static void LoadAll();

	static Texture2D* Floor;
	static Texture2D* Wall1;
	static Texture2D* Wall2;
	static Texture2D* Wall3;
};

Texture2D* AssetBank::Floor = nullptr;
Texture2D* AssetBank::Wall1 = nullptr;
Texture2D* AssetBank::Wall2 = nullptr;
Texture2D* AssetBank::Wall3 = nullptr;

inline void AssetBank::LoadAll()
{
	Floor = PngReader::ReadFromFile("Content/Floor.png");
	Wall1 = PngReader::ReadFromFile("Content/Wall1.png");
	Wall2 = PngReader::ReadFromFile("Content/Wall2.png");
	Wall3 = PngReader::ReadFromFile("Content/Wall3.png");
}

inline void AssetBank::CleanUp()
{
	delete Floor;
	delete Wall1;
	delete Wall2;
	delete Wall3;
}
