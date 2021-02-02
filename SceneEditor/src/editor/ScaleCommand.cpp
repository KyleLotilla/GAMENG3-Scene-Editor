#include "editor/ScaleCommand.h"

ScaleCommand::ScaleCommand(int id, Vec3 oldScale, Vec3 newScale, GameObjectManager* gameObjectManager)
	: m_id(id), m_oldScale(oldScale), m_newScale(newScale), m_gameObjectManager(gameObjectManager)
{
}

ScaleCommand::~ScaleCommand()
{
}

void ScaleCommand::redoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setScale(this->m_newScale);
	}
}

void ScaleCommand::undoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setScale(this->m_oldScale);
	}
}
