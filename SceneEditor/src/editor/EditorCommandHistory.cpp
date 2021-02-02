#include "editor/EditorCommandHistory.h"
#include <iostream>

EditorCommandHistory::EditorCommandHistory()
{
}

EditorCommandHistory::~EditorCommandHistory()
{
}

void EditorCommandHistory::recordExecutedCommand(EditorCommand* command)
{
	if (this->hasRemainingRedo())
	{
		for (int i = this->m_position + 1; i < this->m_commandHistory.size(); i++)
		{
			delete m_commandHistory[i];
		}
		this->m_commandHistory.erase(this->m_commandHistory.begin() + (this->m_position + 1), this->m_commandHistory.end());
	}

	this->m_commandHistory.push_back(command);
	this->m_position++;
}

void EditorCommandHistory::undoCommand()
{
	if (this->hasRemainingUndo())
	{
		this->m_commandHistory[this->m_position]->undoCommand();
		this->m_position--;
	}
}

void EditorCommandHistory::redoCommand()
{
	if (this->hasRemainingRedo())
	{
		this->m_position++;
		this->m_commandHistory[this->m_position]->redoCommand();
	}
}

bool EditorCommandHistory::hasRemainingRedo()
{
	if (this->m_position == this->m_commandHistory.size() - 1 || this->m_commandHistory.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool EditorCommandHistory::hasRemainingUndo()
{
	if (this->m_position < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void EditorCommandHistory::clearHistory()
{
	for (EditorCommand* command : this->m_commandHistory)
	{
		delete command;
	}
	this->m_commandHistory.clear();
}
