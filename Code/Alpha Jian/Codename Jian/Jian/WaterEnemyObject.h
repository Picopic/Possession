//WaterEnemyObject.cpp

#pragma once
#include "Entity.h"

class WaterEnemyObject : public Entity
{
public:
	WaterEnemyObject();
	WaterEnemyObject(Vector2 enemy_position, int width, int height);

	void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type);
	void Update(float deltatime);
	void OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment);
};