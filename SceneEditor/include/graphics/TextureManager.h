#pragma once
#include <unordered_map>
#include <string>
#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void setDevice(ID3D11Device* device);
	void addTexture(std::string path);
	Texture* getTexture(std::string path);
	void releaseTexture(std::string path);
	void release();

private:
	std::unordered_map<std::string, Texture*> m_textures;
	ID3D11Device* m_device;

};