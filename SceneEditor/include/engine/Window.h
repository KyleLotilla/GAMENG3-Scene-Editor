#pragma once
#define NOMINMAX
#include <Windows.h>
#include "backends/imgui_impl_win32.h"

class Window
{
public:
	Window();
	~Window();
	bool init();
	bool release();
	void broadcast();
	bool isRunning();
	RECT getClientWindowRect();
	HWND getHandle();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

protected:
	HWND m_hwnd;
	bool m_isRun = true;
};