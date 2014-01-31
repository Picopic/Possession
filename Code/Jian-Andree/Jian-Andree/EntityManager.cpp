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
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(0, std::pair<Alignment, Alignment> (PLAYER, WATERFOE)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(1, std::pair<Alignment, Alignment> (PLAYER, WOODFOE)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(2, std::pair<Alignment, Alignment> (PLAYER, FIREFOE)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(3, std::pair<Alignment, Alignment> (PLAYER, WATERFOEBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(4, std::pair<Alignment, Alignment> (PLAYER, WOODFOEBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(5, std::pair<Alignment, Alignment> (PLAYER, FIREFOEBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(6, std::pair<Alignment, Alignment> (WATERFOE, PLAYER)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(7, std::pair<Alignment, Alignment> (WATERFOE, FRIENDBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(8, std::pair<Alignment, Alignment> (WOODFOE, PLAYER)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(9, std::pair<Alignment, Alignment> (WOODFOE, FRIENDBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(10, std::pair<Alignment, Alignment> (FIREFOE, PLAYER)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(11, std::pair<Alignment, Alignment> (FIREFOE, FRIENDBULLET)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(12, std::pair<Alignment, Alignment> (FRIENDBULLET, WATERFOE)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(13, std::pair<Alignment, Alignment> (FRIENDBULLET, WOODFOE)));
	CollisionMap.insert (std::pair<int, std::pair<Alignment, Alignment>>(14, std::pair<Alignment, Alignment> (FRIENDBULLET, FIREFOE)));
}

void EntityManager::AttachEntity(Alignment entity_name, Vector2 position, int width, int height)
{
	/*
		create new entity, appropriate to the string that followed
	*/

	//Entity* entity = new WaterEnemyObject(position, width, height);

	switch(entity_name)
	{
	case WATERFOE:
		game_entities.push_back(new WaterEnemyObject(position, width, height));
		game_entities[game_entities.size()-1]->Init("Water enemy");
		break;
	case FIREFOE:
		game_entities.push_back(new FireEnemyObject(position, width, height));
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

void EntityManager::Cleanup()
{
	for(int i = 0; i < game_entities.size(); i ++)
	{
		game_entities.erase(game_entities.begin() + i);
	}
}