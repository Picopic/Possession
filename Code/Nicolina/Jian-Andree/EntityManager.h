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

	void Init(Keyboard* keyboard);
	void AttachEntity(Alignment entity_name, Vector2 position, int width, int height, Type type);
	void DetachEntity(int entity_index);
	void Update(float deltatime);

	void Cleanup();
	std::vector<Entity*> game_entities;
private:
	
	std::map<std::pair<Alignment, Alignment>, int> CollisionMap;
};