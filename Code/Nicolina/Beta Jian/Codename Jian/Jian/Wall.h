//Wall.h

#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall();

	Wall(Vector2 entity_position, int entity_width, int entity_height);

	void Init(std::string object_type, Alignment alignment, Type type);

	void Update(float deltatime);

	void OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment);

private:

};