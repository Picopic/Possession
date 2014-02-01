//PlayerObject.h

#pragma once
#include "Entity.h"
#include "Input.h"

class PlayerObject : public Entity
{
public:
	PlayerObject();
	PlayerObject(Vector2 player_position, int width, int height, Keyboard* keyboard);

	void Init(std::string object_type, Alignment player_alignment, Type player_type);
	void Update(float deltatime);
	void getID();
	void setID();

	void OnCollision(Type type);

private:
	//need inputs, so a keyboard is necessary
	Keyboard* player_keyboard;
};