#pragma once

class EditorCommand
{
public:
	virtual void redoCommand() = 0;
	virtual void undoCommand() = 0;
};