#pragma once
#include "GameObject.h"
#include "input/InputListener.h"
#include "window/Window.h"

class Camera : public GameObject, public InputListener
{
public:
	Camera();
	~Camera();
	virtual void update(float deltaTime);
	virtual void draw(DeviceContext* deviceContext, ViewportParams viewportParams);
	Mat4 getViewMatrix();
	void updateViewMatrix();
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
	virtual void onMouseMove(const Vec2& mouse_pos, const Vec2& deltaPos);
	virtual void onRightMouseDown(const Vec2& mouse_pos);
	virtual void onRightMouseUp(const Vec2& mouse_pos);

private:
	Mat4 m_viewMatrix;
	float m_sensitivity = 0.03f;
	float m_movementSpeed = 5.0f;
	float m_speedZ = 0.0f;
	float m_speedX = 0.0f;
	float m_rotationX = 0.0f;
	float m_rotationY = 0.0f;
	bool m_canMove = false;
};
