//EntityManager.h

#pragma once
#include "Collider.h"
#include "Entity.h"
#include "WaterEnemyObject.h"
#include "FireEnemyObject.h"
#include "PlayerObject.h"


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void Init();
	void AttachEntity(Alignment entity_name, Vector2 position, int width, int height);
	void DetachEntity(int entity_index);

	void Cleanup();
	std::vector<Entity*> game_entities;
private:
	
	std::map<int, std::pair<Alignment, Alignment>> CollisionMap;
};