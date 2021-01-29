#include "input/CursorManager.h"
#include <Windows.h>

void CursorManager::setCursorPosition(int x, int y)
{
	SetCursorPos(x, y);
}

void CursorManager::showCursor(bool show)
{
	ShowCursor(show);
}
