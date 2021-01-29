#pragma once
#include "InputListener.h"
#include "CursorManager.h"
#include <unordered_set>

class InputEngine
{
public:
	InputEngine();
	~InputEngine();
	void pollInput();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	CursorManager* getCursorManager();

private:
	std::unordered_set<InputListener*> m_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Vec2 m_old_mouse_pos;
	bool m_first_time = true;
	CursorManager m_cursorManager;
};
