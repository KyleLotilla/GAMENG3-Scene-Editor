#pragma once
#include "EditorState.h"

class EditorStateListener
{
public:
	virtual void stateUpdated(EditorState oldState, EditorState newState) = 0;
};