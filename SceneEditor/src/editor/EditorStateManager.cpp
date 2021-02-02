#include "editor/EditorStateManager.h"

EditorStateManager::EditorStateManager()
{
}

EditorStateManager::~EditorStateManager()
{
}

void EditorStateManager::setEditorState(EditorState state)
{
	for (EditorStateListener* listener : this->m_listeners)
	{
		listener->stateUpdated(this->m_currentState, state);
	}
	this->m_currentState = state;
}

EditorState EditorStateManager::getCurrentState()
{
	return this->m_currentState;
}

void EditorStateManager::addListener(EditorStateListener* listener)
{
	this->m_listeners.push_back(listener);
}
