#pragma once
#include "math/Vec2.h"

class InputListener
{
public:
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	virtual void onMouseMove(const Vec2& mouse_pos, const Vec2& deltaPos);

	virtual void onLeftMouseDown(const Vec2& mouse_pos);
	virtual void onLeftMouseUp(const Vec2& mouse_pos);

	virtual void onRightMouseDown(const Vec2& mouse_pos);
	virtual void onRightMouseUp(const Vec2& mouse_pos);

};
