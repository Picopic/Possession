// LostSoulObject.h

#pragma once
#include "Entity.h"
#include "PlayerObject.h"

class LostSoulObject : public Entity
{
public:
	LostSoulObject();
	LostSoulObject(Entity* enemydropping, Vector2 lostsoul_position, ConfigManager* config_mgr);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment other_alignment);
};