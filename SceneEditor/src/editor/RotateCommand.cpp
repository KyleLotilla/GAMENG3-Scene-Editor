#include "editor/RotateCommand.h"

RotateCommand::RotateCommand(int id, reactphysics3d::Quaternion oldRotation, reactphysics3d::Quaternion newRotation, GameObjectManager* gameObjectManager) :
	m_id(id), m_oldRotation(oldRotation), m_newRotation(newRotation), m_gameObjectManager(gameObjectManager)
{
}

RotateCommand::~RotateCommand()
{
}

void RotateCommand::redoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setRotation(this->m_newRotation);
	}
}

void RotateCommand::undoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setRotation(this->m_oldRotation);
	}
}
