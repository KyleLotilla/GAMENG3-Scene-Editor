#pragma once
#include "game/GameObjectManager.h"
#include "editor/EditorCommand.h"

class ScaleCommand : public EditorCommand
{
public:
	ScaleCommand(int id, Vec3 oldScale, Vec3 newScale, GameObjectManager* gameObjectManager);
	~ScaleCommand();
	void redoCommand();
	void undoCommand();

private:
	int m_id;
	Vec3 m_oldScale;
	Vec3 m_newScale;
	GameObjectManager* m_gameObjectManager;
};
