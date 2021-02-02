#pragma once
#include "game/GameObjectManager.h"
#include "editor/EditorCommand.h"

class RotateCommand : public EditorCommand
{
public:
	RotateCommand(int id, reactphysics3d::Quaternion oldRotation, reactphysics3d::Quaternion newRotation, GameObjectManager* gameObjectManager);
	~RotateCommand();
	void redoCommand();
	void undoCommand();

private:
	int m_id;
	reactphysics3d::Quaternion m_oldRotation;
	reactphysics3d::Quaternion m_newRotation;
	GameObjectManager* m_gameObjectManager;
};