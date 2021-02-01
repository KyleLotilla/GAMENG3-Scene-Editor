#include "game/Camera.h"

Camera::Camera()
{
	this->m_localPosition.m_z = -4.0f;
	updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	if (this->m_speedX != 0.0f || this->m_speedZ != 0.0f)
	{
		this->m_localPosition.m_x += this->m_speedX * deltaTime;
		this->m_localPosition.m_z += this->m_speedZ * deltaTime;
		this->updateViewMatrix();
	}
}

void Camera::draw(DeviceContext * deviceContext, ViewportParams viewportParams)
{
}

Mat4 Camera::getViewMatrix()
{
	return this->m_viewMatrix;
}

void Camera::updateViewMatrix()
{
	Mat4 rotationXMatrix;
	Mat4 rotationYMatrix;
	Mat4 translationMatrix;
	Mat4 newViewMatrix;

	rotationXMatrix.setRotationX(this->m_rotationX);
	rotationYMatrix.setRotationY(this->m_rotationY);
	translationMatrix.setTranslation(this->m_localPosition);

	newViewMatrix = translationMatrix * rotationYMatrix * rotationXMatrix;
	newViewMatrix = newViewMatrix.inverse();

	this->m_viewMatrix = newViewMatrix;
}

void Camera::onKeyDown(int key)
{
	if (key == 'W')
	{
		this->m_speedZ = this->m_movementSpeed;
	}
	else if (key == 'S')
	{
		this->m_speedZ = -this->m_movementSpeed;
	}

	if (key == 'A')
	{
		this->m_speedX = -this->m_movementSpeed;
	}
	else if (key == 'D')
	{
		this->m_speedX = this->m_movementSpeed;
	}
}

void Camera::onKeyUp(int key)
{
	if (key == 'W' && this->m_speedZ > 0.0f)
	{
		this->m_speedZ = 0.0f;
	}
	else if (key == 'S' && this->m_speedZ < 0.0f)
	{
		this->m_speedZ = 0.0f;
	}

	if (key == 'A' && this->m_speedX < 0.0f)
	{
		this->m_speedX = 0.0f;
	}
	else if (key == 'D' && this->m_speedX > 0.0f)
	{
		this->m_speedX = 0.0f;
	}
}

void Camera::onMouseMove(const Vec2 & mouse_pos, const Vec2& deltaPos)
{
	if (this->m_canMove)
	{
		this->m_rotationX += deltaPos.m_y * m_sensitivity;
		this->m_rotationY += deltaPos.m_x * m_sensitivity;
		this->updateViewMatrix();
	}
}

void Camera::onRightMouseDown(const Vec2 & mouse_pos)
{
	this->m_canMove = true;
}

void Camera::onRightMouseUp(const Vec2 & mouse_pos)
{
	this->m_canMove = false;
}
