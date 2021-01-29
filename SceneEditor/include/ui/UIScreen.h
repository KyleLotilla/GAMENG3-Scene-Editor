#pragma once
#include "graphics/ViewportParams.h"

class UIScreen
{
public:
	virtual void update(float deltaTime) = 0;
	virtual void drawUI(ViewportParams viewportParams) = 0;
	void setActive(bool active);

protected:
	bool m_active = true;
};