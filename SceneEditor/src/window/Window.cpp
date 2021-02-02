#include "window/Window.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

Window::Window()
{
}

Window::~Window()
{
	this->release();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}

	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
			Window* const window = reinterpret_cast<Window* const>(params->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			break;
		}
		case WM_DESTROY:
		{
			Window* const window = reinterpret_cast<Window* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			window->onDestroy();
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "DEFAULT_WINDOW_CLASS";
	wc.lpszMenuName = "";
	wc.lpfnWndProc = &WndProc;

	if (!(RegisterClassEx(&wc)))
		return false;

	this->m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "DEFAULT_WINDOW_CLASS", "Scene Editor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 720, NULL, NULL, NULL, this);
	this->onCreate();

	if (!this->m_hwnd)
		return false;

	ShowWindow(this->m_hwnd, SW_SHOW);
	UpdateWindow(this->m_hwnd);

	return true;
}

bool Window::release()
{
	if (!DestroyWindow(this->m_hwnd))
		return false;

	return true;
}

void Window::broadcast()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (this->m_isRun)
		onUpdate();
}

bool Window::isRunning()
{
	return this->m_isRun;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	GetClientRect(this->m_hwnd, &rc);
	return rc;
}

HWND Window::getHandle()
{
	return this->m_hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	this->m_isRun = false;
}
