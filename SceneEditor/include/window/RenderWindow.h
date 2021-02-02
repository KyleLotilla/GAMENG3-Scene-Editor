#pragma once
#include "window/Window.h"
#include "graphics/GraphicsEngine.h"

class RenderWindow : public Window
{
public:
	RenderWindow(GraphicsEngine* graphicsEngine);
	~RenderWindow();
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	bool present(bool vsync);
	void clearRenderTargetColor(float red, float green, float blue, float alpha);

protected:
	GraphicsEngine* m_graphicsEngine;
	SwapChain* m_swapChain;
};
