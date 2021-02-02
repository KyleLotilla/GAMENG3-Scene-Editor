#pragma once
#include "game/GameObjectManager.h"
#include "editor/EditorCommand.h"

class TranslateCommand : public EditorCommand
{
public:
	TranslateCommand(int id, Vec3 oldPosition, Vec3 newPosition, GameObjectManager* gameObjectManager);
	~TranslateCommand();
	void redoCommand();
	void undoCommand();

private:
	int m_id;
	Vec3 m_oldPosition;
	Vec3 m_newPosition;
	GameObjectManager* m_gameObjectManager;
};