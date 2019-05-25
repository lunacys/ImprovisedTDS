#pragma once
#include <string>
#include <map>

#include "Texture2D.hpp"
#include "Shader.hpp"
#include "PngReader.hpp"

enum class AssetType
{
	Texture2D,
	Shader
};

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	//void LoadTexture2D(const std::string& pngFilePath);
	//void LoadShader(const std::string& shaderFilePath);
	void LoadAsset(const std::string& filePath, AssetType assetType);

	Texture2D* GetTexture2D(const std::string& pngFilePath);
	Shader* GetShader(const std::string& shadersFilePath);

	void SetRootDirectory(const std::string& path);
	std::string GetRootDirectory() const;

private:
	std::map<std::string, Texture2D*> texture2dCache_;
	std::map<std::string, Shader*> shaderCache_;
	std::string rootDir_ = "";
};

inline ContentManager::ContentManager()
{ }


inline ContentManager::~ContentManager()
{
	for (auto tex2d = texture2dCache_.begin(); tex2d != texture2dCache_.end(); ++tex2d)
		delete tex2d->second;

	for (auto shader = shaderCache_.begin(); shader != shaderCache_.end(); ++shader)
		delete shader->second;

	texture2dCache_.clear();
	shaderCache_.clear();
}

inline void ContentManager::LoadAsset(const std::string& filePath, AssetType assetType)
{
	try
	{
		std::cout << "> Loading Asset " << filePath << std::endl;
		std::string path = 
			rootDir_ == "" 
			? filePath 
			: rootDir_ + "/" + filePath;

		switch(assetType)
		{
			case AssetType::Texture2D:
				texture2dCache_[filePath] = PngReader::ReadFromFile(path);
				break;
			case AssetType::Shader: 
				shaderCache_[filePath] = Shader::ReadFromFile(path);
				break;
			default: 
				std::cerr << "WARNING: Unsupported asset type, skipping" << std::endl;
				break;
		}
		std::cout << "> End Loading Asset " << filePath << std::endl;
	}
	catch(std::runtime_error e)
	{
		std::cerr << "ERROR: Couldn't read the file specified; Log: \n"
			<< e.what() << std::endl;
	}
}

inline Texture2D* ContentManager::GetTexture2D(const std::string& pngFilePath)
{
	// Find asset with specified id
	//auto p = texture2dCache_.find(pngFilePath);
	// If asset wasn't found in cache, throw an runtime error
	//if (p == texture2dCache_.end())
		//throw std::runtime_error("ERROR: There's no Texture2D with specified value in cache.\nMake sure you've loaded it with LoadTexture2D fuction");
	//std::cout << "> Getting Texture2D" << pngFilePath << std::endl;
	return texture2dCache_[pngFilePath];
}

inline Shader* ContentManager::GetShader(const std::string& shadersFilePath)
{
	//auto p = shaderCache_.find(shadersFilePath);
	//if (p == shaderCache_.end())
		//throw std::runtime_error("ERROR: There's no Shader with specified value in cache.\nMake sure you've loaded it with LoadShader fuction");
	//std::cout << "> Getting Shader" << shadersFilePath << std::endl;
	return shaderCache_[shadersFilePath];
}

inline void ContentManager::SetRootDirectory(const std::string& path)
{
	rootDir_ = path;
}

inline std::string ContentManager::GetRootDirectory() const
{
	return rootDir_;
}
