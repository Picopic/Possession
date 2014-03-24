//Drawmanager.h

#pragma once
#include "EntityManager.h"
#include "HeadsUpDisplay.h"

class DrawManager
{
public:
	DrawManager();

	void Draw(sf::RenderWindow *window, EntityManager *entity_manager, HeadsUpDisplay* HUD, bool draw_hitbox);

	void SortEntities(EntityManager* entity_mgr);

	std::vector<Entity*> sorted_entity_mgr;
};