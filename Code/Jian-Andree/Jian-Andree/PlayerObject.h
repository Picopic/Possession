//PlayerObject.h

#pragma once
#include "Entity.h"

class PlayerObject : public Entity
{
public:
	PlayerObject();
	PlayerObject(Vector2 player_position, int width, int height);

	void Init(std::string object_type, Alignment player_alignment, Type player_type);
	void Update(float deltatime);
	void getID();
	void setID();

	void OnCollision(Type type, Vector2 offset, Alignment enemy_alignment);

private:
};