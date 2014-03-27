//FireEnemyObject

#pragma once
#include "Entity.h"


class FireEnemyObject : public Entity
{
public:
	FireEnemyObject();
	FireEnemyObject(ConfigManager* config_manager, Vector2 enemy_position);

	void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type);
	void Update(float deltatime);

	void AddSounds(SoundManager* sound_mgr);

	void OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment);

private:
	// AI functions
	void Movement(float Deltatime);
	void Attack();
};