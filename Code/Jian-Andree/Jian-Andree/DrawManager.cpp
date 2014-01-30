//Drawmanager.cpp
#include "stdafx.h"
#include "DrawManager.h"



DrawManager::DrawManager()
{

}

void DrawManager::Draw(sf::RenderWindow *window, EntityManager *entity_manager)
{
	window->clear(sf::Color(0x11,0x22,0x33,0xff));

	for(int i = 0; i < entity_manager->game_entities.size(); i++)
	{
		//window->draw(entity_manager->game_entities[i]->shape);
	}

	window->display();
}