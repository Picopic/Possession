//Drawmanager.h

#pragma once
#include "EntityManager.h"

class DrawManager
{
public:
	DrawManager();

	void Draw(sf::RenderWindow *window, EntityManager *entity_manager);
};