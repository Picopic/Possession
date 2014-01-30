//EntityManager.cpp

#include "stdafx.h"

#include "EntityManager.h"

EntityManager::EntityManager()
{
	
}

EntityManager::~EntityManager()
{

}

void EntityManager::Init()
{
	//CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(0, std::pair<PLAYER, WATERFOE>)
}

void EntityManager::AttachEntity(Alignment entity_name, Vector2 position, int width, int height)
{
	/*
		create new entity, appropriate to the string that followed
	*/
	switch(entity_name)
	{
	case WATERFOE:
		game_entities.push_back(&WaterEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->Init("Water enemy");
		break;
	case FIREFOE:
		game_entities.push_back(&FireEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->Init("Fire enemy");
		break;
	}
	
}

void EntityManager::DetachEntity(int entity_index)
{
	/*
		Delete the entity, appropriate to the string that followed
	*/
}