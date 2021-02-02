#pragma once
#include "EditorStateListener.h"
#include <vector>

class EditorStateManager
{
public:
	EditorStateManager();
	~EditorStateManager();
	void setEditorState(EditorState state);
	EditorState getCurrentState();
	void addListener(EditorStateListener* listener);

private:
	EditorState m_currentState = EditorState::NOT_SET;
	std::vector<EditorStateListener*> m_listeners;
};
