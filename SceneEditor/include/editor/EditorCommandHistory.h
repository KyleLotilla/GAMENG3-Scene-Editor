#pragma once
#include "EditorCommand.h"
#include <vector>

class EditorCommandHistory
{
public:
	EditorCommandHistory();
	~EditorCommandHistory();
	void recordExecutedCommand(EditorCommand* command);
	void undoCommand();
	void redoCommand();
	bool hasRemainingRedo();
	bool hasRemainingUndo();
	void clearHistory();

private:
	int m_position = -1;
	std::vector<EditorCommand*> m_commandHistory;
};
