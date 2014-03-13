// AltarObject.h

#pragma once
#include "Entity.h"

class AltarObject : public Entity
{
public:
	AltarObject();
	AltarObject(Vector2 altar_position, ConfigManager* config_mgrt);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Entity* collision_entity, Type altar_type, Vector2 offset, Alignment altar_alignment);
};