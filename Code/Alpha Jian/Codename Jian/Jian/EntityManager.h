//EntityManager.h

#pragma once
#include "Collider.h"
#include "Entity.h"
#include "WaterEnemyObject.h"
#include "FireEnemyObject.h"
#include "PlayerObject.h"
#include "Projectile.h"
#include "LostSoulObject.h"
#include "Wall.h"
#include "Spritemanager.h"
#include "SoundManager.h"
#include "EnemyWaves.h"
#include "ConfigManager.h"

class EntityManager
{
public:
	EntityManager();
	EntityManager(SpriteManager* sprite_mgr, SoundManager* sound_mgr);
	~EntityManager();

	void Init();
	void AttachEntity(Alignment entity_name, Vector2 position, int width, int height, Type type);
	void DetachEntity(int entity_index);
	void Update(float deltatime);

	void AttachProjectile(Alignment entity_name, Entity* shooter, int width, int height, Type entity_type, Vector2 entity_direction);
	void AttachWall(Vector2 position, int width, int height, Type wall_type);

	void Cleanup();
	std::vector<Entity*> game_entities;
private:
	std::map<std::pair<Alignment, Alignment>, int> CollisionMap;
	SpriteManager* sprite_manager;
	SoundManager* sound_manager;

	//Input from files
	ConfigManager* config_manager;

	EnemyWaves* waves;
};