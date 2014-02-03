//PlayerObject.cpp

#include "stdafx.h"

#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

}

PlayerObject::PlayerObject(Vector2 player_position, int player_width, int player_height, Keyboard* keyboard)
{
	position = player_position;
	width = player_width;
	height = player_height;

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);

	player_keyboard = keyboard;
}

void PlayerObject::Init(std::string object_type, Alignment player_alignment, Type player_type)
{
	entity_ID = object_type;

	alignment = player_alignment;
	type = player_type;

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(position.x, position.y);
	
	shape.setFillColor(sf::Color(0,255,0));
	std::cout << "Playerobject: " << position.x << std::endl;
}

void PlayerObject::Update(float deltatime)
{
	//vertical movement
	if(player_keyboard->getW())
	{
		shape.move(0, -200 * deltatime);
		collider->position.y -= 200*deltatime;
	}
	else if(player_keyboard->getS())
	{
		shape.move(0, 200 * deltatime);
		collider->position.y += 200*deltatime;
	}
	//horizontal movement
	if(player_keyboard->getA())
	{
		shape.move(-200 * deltatime, 0);
		collider->position.x -= 200*deltatime;
	}
	else if(player_keyboard->getD())
	{
		shape.move(200 * deltatime, 0);
		collider->position.x += 200*deltatime;
	}

	if(player_keyboard->getR())
	{
		
	}
}

void PlayerObject::OnCollision(Type type, Vector2 offset)
{
	//shape.move(offset.x, offset.y);
	std::cout << "x" << offset.x << std::endl;
	std::cout << "y" << offset.y << std::endl;
}