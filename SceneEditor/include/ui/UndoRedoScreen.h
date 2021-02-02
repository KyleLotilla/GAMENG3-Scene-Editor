#pragma once
#include "UIScreen.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "editor/EditorCommandHistory.h"
#include "editor/EditorStateListener.h"

class UndoRedoScreen : public UIScreen, public EditorStateListener
{
public:
	UndoRedoScreen();
	~UndoRedoScreen();
	void setEditorCommandHistory(EditorCommandHistory* commandHistory);
	virtual void update(float deltaTime);
	virtual void drawUI(ViewportParams viewportParams);
	void stateUpdated(EditorState oldState, EditorState newState);

private:
	EditorCommandHistory* m_commandHistory;
	EditorState m_currentState;
};