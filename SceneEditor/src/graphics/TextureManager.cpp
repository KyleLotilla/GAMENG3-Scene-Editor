#include "graphics/TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::setDevice(ID3D11Device* device)
{
	this->m_device = device;
}

void TextureManager::addTexture(std::string path)
{
	if (this->m_textures.find(path) == this->m_textures.end())
	{
		Texture* texture = new Texture();
		texture->init(path, this->m_device);
		this->m_textures[path] = texture;
	}
}

Texture* TextureManager::getTexture(std::string path)
{
	if (this->m_textures.find(path) != this->m_textures.end())
	{
		return this->m_textures[path];
	}
	else
	{
		return nullptr;
	}
}

void TextureManager::releaseTexture(std::string path)
{
	if (this->m_textures.find(path) != this->m_textures.end())
	{
		this->m_textures[path]->release();
		delete this->m_textures[path];
		this->m_textures.erase(path);
	}
}

void TextureManager::release()
{
	for (auto textureMapping : this->m_textures)
	{
		textureMapping.second->release();
		delete textureMapping.second;
	}
	this->m_textures.clear();
}
