// AltarObject.h

#pragma once
#include "Entity.h"

class AltarObject : public Entity
{
public:
	AltarObject();
	AltarObject(Vector2 altar_position, int width, int height);

	void Init(std::string object_type, Alignment alignment, Type type);
	void Update(float deltatime);

	void OnCollision(Type altar_type, Vector2 offset, Alignment altar_alignment);
};