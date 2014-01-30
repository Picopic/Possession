//PlayerObject.h

#pragma once
#include "Entity.h"

class PlayerObject : public Entity
{
public:
	PlayerObject();
	PlayerObject(Vector2 player_position, int width, int height);

	void Init(std::string object_type);
	void Update(float deltatime);
	void getID();
	void setID();

private:
	//need inputs, so a keyboard is necessary
};