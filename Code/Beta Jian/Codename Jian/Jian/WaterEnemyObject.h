//WaterEnemyObject.cpp

#pragma once
#include "Entity.h"

class WaterEnemyObject : public Entity
{
public:
	WaterEnemyObject();
	WaterEnemyObject(ConfigManager* config_mgr, Vector2 enemy_position);

	void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type);
	void Update(float deltatime);
	
	void AddSounds(SoundManager* sound_mgr);
	
	void OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment);

private:
	void Attack();
	void Movement(float Deltatime);
};