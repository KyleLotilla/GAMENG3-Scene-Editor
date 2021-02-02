#include "editor/TranslateCommand.h"

TranslateCommand::TranslateCommand(int id, Vec3 oldPosition, Vec3 newPosition, GameObjectManager* gameObjectManager) :
	m_id(id), m_oldPosition(oldPosition), m_newPosition(newPosition), m_gameObjectManager(gameObjectManager)
{
}

TranslateCommand::~TranslateCommand()
{
}

void TranslateCommand::redoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setPosition(this->m_newPosition);
	}
}

void TranslateCommand::undoCommand()
{
	GameObject* gameObject = this->m_gameObjectManager->getGameObject(this->m_id);
	if (gameObject)
	{
		gameObject->setPosition(this->m_oldPosition);
	}
}
