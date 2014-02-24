//Drawmanager.cpp
#include "stdafx.h"
#include "DrawManager.h"
#include "AnimatedSprite.h"

DrawManager::DrawManager()
{

}

void DrawManager::Draw(sf::RenderWindow *window, EntityManager *entity_manager, HeadsUpDisplay* HUD)
{
	SortEntities(entity_manager);

	for(int i = (sorted_entity_mgr.size() - 1); i >= 0; i--)
	{
		window->draw(*sorted_entity_mgr[i]->GetCurrentAnimation()->getSprite());
	}

	HUD->DrawHUD(window);

	window->display();
}

void DrawManager::SortEntities(EntityManager* entity_mgr)
{
	int i, j;
	sorted_entity_mgr.clear();
	for(int ex = 0; ex < entity_mgr->game_entities.size(); ex++)
	{
		sorted_entity_mgr.push_back(entity_mgr->game_entities[ex]);
	}

	Entity* temp_entity;
	for(i = 1; i < sorted_entity_mgr.size(); i++)
	{
		temp_entity = sorted_entity_mgr[i];

		for(j = i-1; (j >= 0) && (sorted_entity_mgr[j]->getPosition().y < temp_entity->getPosition().y); j--)
		{
			sorted_entity_mgr[j+1] = sorted_entity_mgr[j];
		}
		sorted_entity_mgr[j+1] = temp_entity;
	}
}
