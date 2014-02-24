//Drawmanager.h

#pragma once
#include "EntityManager.h"
#include "HeadsUpDisplay.h"

class DrawManager
{
public:
	DrawManager();

	void Draw(sf::RenderWindow *window, EntityManager *entity_manager, HeadsUpDisplay* HUD);

	void SortEntities(EntityManager* entity_mgr);

	std::vector<Entity*> sorted_entity_mgr;
};