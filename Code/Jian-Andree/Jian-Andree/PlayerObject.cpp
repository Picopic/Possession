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

	flagged_for_death = false;
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = 1.0f;

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
}

void PlayerObject::Update(float deltatime)
{
	//Vertical movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0, -200 * deltatime);
		collider->position.y -= 200 * deltatime;
		position.y -= 200*deltatime;
		direction.y = -1;
		direction.x = 0;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0, 200 * deltatime);
		collider->position.y += 200*deltatime;
		position.y += 200*deltatime;
		direction.y = 1;
		direction.x = 0;
	}
	//horizontal movement
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-200 * deltatime, 0);
		collider->position.x -= 200*deltatime;
		position.x -= 200*deltatime;
		direction.y = 0;
		direction.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move(200 * deltatime, 0);
		collider->position.x += 200*deltatime;
		position.x += 200*deltatime;
		direction.y = 0;
		direction.x = 1;
	}

	if(created_projectile)
	{
		shooting_delay += deltatime;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		create_projectile = true;
		created_projectile = true;
	}
	else
	{
		create_projectile = false;
	}

	if(shooting_delay > delay)
	{
		shooting_delay = 0.001f;
		created_projectile = false;
	}
}

void PlayerObject::OnCollision(Type type, Vector2 offset)
{
	//shape.move(offset.x, offset.y);
	std::cout << "x" << offset.x << std::endl;
	std::cout << "y" << offset.y << std::endl;
}