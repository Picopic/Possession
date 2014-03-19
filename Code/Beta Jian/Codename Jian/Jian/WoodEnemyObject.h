//WoodEnemyObject.h

#pragma once
#include "Entity.h"

class WoodEnemyObject : public Entity
{
	public:
	WoodEnemyObject();
	WoodEnemyObject(ConfigManager* config_manager, Vector2 enemy_position);

	void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type);
	void Update(float deltatime);

	void OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment);

private:
	void Movement(float Deltatime);

	void Attack();
};