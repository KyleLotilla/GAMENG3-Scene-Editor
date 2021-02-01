#pragma once
#include "Texture.h"
#include "game/Component.h"
#include "math/Vec4.h"

class TextureComponent : public Component
{
public:
	TextureComponent();
	~TextureComponent();
	Texture* getTexture();
	void setTexture(Texture* texture);
	Vec4 getColor();
	void setColor(Vec4 color);

private:
	Texture* m_texture;
	Vec4 m_color;
};
