#include "window/RenderWindow.h"

RenderWindow::RenderWindow(GraphicsEngine* graphicsEngine)
	: m_graphicsEngine(graphicsEngine)
{
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::onCreate()
{
	Window::onCreate();
	this->m_swapChain = m_graphicsEngine->createSwapChain();
	RECT rc = this->getClientWindowRect();
	this->m_swapChain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
}

void RenderWindow::onUpdate()
{
	Window::onUpdate();
}

void RenderWindow::onDestroy()
{
	Window::onDestroy();
	this->m_swapChain->release();
}

bool RenderWindow::present(bool vsync)
{
	this->m_swapChain->present(vsync);
	return true;
}

void RenderWindow::clearRenderTargetColor(float red, float green, float blue, float alpha)
{
	this->m_graphicsEngine->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swapChain,
		red, green, blue, alpha);
}
