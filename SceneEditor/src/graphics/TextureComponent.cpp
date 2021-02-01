#include "graphics/TextureComponent.h"

TextureComponent::TextureComponent()
{
	this->m_type = ComponentType::TEXTURE;
	this->m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

TextureComponent::~TextureComponent()
{
}

Texture* TextureComponent::getTexture()
{
	return this->m_texture;
}

void TextureComponent::setTexture(Texture* texture)
{
	this->m_texture = texture;
}

Vec4 TextureComponent::getColor()
{
	return this->m_color;
}

void TextureComponent::setColor(Vec4 color)
{
	this->m_color = color;
}
