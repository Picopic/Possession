//FireEnemyObject

#pragma once
#include "Entity.h"

class FireEnemyObject : public Entity
{
	public:
	FireEnemyObject();
	FireEnemyObject(Vector2 enemy_position, int width, int height);

	void Init(std::string object_type);
	void Update(float deltatime);
};