#include "input/InputEngine.h"
#include <Windows.h>

InputEngine::InputEngine()
{
}

InputEngine::~InputEngine()
{
}

void InputEngine::pollInput()
{
	POINT current_mouse_pos = {};
	GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		for (InputListener* listener : m_listeners)
		{
			listener->onMouseMove(Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y), Vec2(current_mouse_pos.x - m_old_mouse_pos.m_x, current_mouse_pos.y - m_old_mouse_pos.m_y));
		}
	}
	m_old_mouse_pos = Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y);


	if (GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keys_state[i] & 0x80)
			{
				for (InputListener* listener : m_listeners)
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							listener->onLeftMouseDown(Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							listener->onRightMouseDown(Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y));
					}
					else
					{
						listener->onKeyDown(i);
					}
				}
			}
			else
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					for (InputListener* listener : m_listeners)
					{
						if (i == VK_LBUTTON)
						{
							if (m_keys_state[i] != m_old_keys_state[i])
								listener->onLeftMouseUp(Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y));
						}
						else if (i == VK_RBUTTON)
						{
							if (m_keys_state[i] != m_old_keys_state[i])
								listener->onRightMouseUp(Vec2((float)current_mouse_pos.x, (float)current_mouse_pos.y));
						}
						else
						{
							listener->onKeyUp(i);
						}
					}
				}

			}

		}

		memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputEngine::addListener(InputListener * listener)
{
	this->m_listeners.insert(listener);
}

void InputEngine::removeListener(InputListener * listener)
{
	this->m_listeners.erase(listener);
}

CursorManager * InputEngine::getCursorManager()
{
	return &(m_cursorManager);
}
