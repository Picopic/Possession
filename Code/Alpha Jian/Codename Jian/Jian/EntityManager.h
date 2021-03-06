//EntityManager.h

#pragma once
#include "Collider.h"
#include "Entity.h"
#include "WaterEnemyObject.h"
#include "FireEnemyObject.h"
#include "WoodEnemyObject.h"
#include "PlayerObject.h"
#include "Projectile.h"
#include "LostSoulObject.h"
#include "Wall.h"
#include "AltarObject.h"
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

	void Init(EnemyWaves* enemywavesptr);
	void AttachEntity(Alignment entity_name, Vector2 position, Type type);
	void DetachEntity(int entity_index);
	void Update(float deltatime);

	void AttachProjectile(Alignment entity_name, Entity* shooter, int width, int height, Type entity_type, Vector2 entity_direction);
	void AttachWall(Vector2 position, int width, int height, Type wall_type);
	void AttachLostSoul(Alignment entity_name, Entity* enemydropping, int width, int height, Type entity_type, Vector2 entity_position);
	void AttachAltar(Alignment entity_name, int width, int height, Type entity_type, Vector2 entity_position);

	void Cleanup();
	std::vector<Entity*> game_entities;
private:
	std::map<std::pair<Alignment, Alignment>, int> CollisionMap;
	SpriteManager* sprite_manager;
	SoundManager* sound_manager;

	//Input from files
	ConfigManager* config_manager;

	int playerheight, playerwidth;
	int fireprojectileheight, fireprojectilewidth;
	int waterprojectileheight, waterprojectilewidth;
	int woodprojectileheight, woodprojectilewidth;

	int fireheight, firewidth;
	int waterheight, waterwidth;
	int woodheight, woodwidth;

	EnemyWaves* waves;
};