// LostSoulObject.h

#pragma once
#include "Entity.h"
#include "PlayerObject.h"

class LostSoulObject : public Entity
{
public:
	LostSoulObject();
	LostSoulObject(Vector2 lostsoul_position, int width, int height);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Type collision_type, Vector2 offset, Alignment other_alignment);
};