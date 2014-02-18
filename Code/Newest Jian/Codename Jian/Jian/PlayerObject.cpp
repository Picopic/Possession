//PlayerObject.cpp

#include "stdafx.h"

#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

}

PlayerObject::PlayerObject(Vector2 player_position, int player_width, int player_height)
{
	current_animation = nullptr;
	direction = Vector2(1, 0);

	position = player_position;
	width = player_width;
	height = player_height;

	flagged_for_death = false;
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = 0.01f;

	velocity = 200;

	collider = new Collider;
	collider->position = position;
	collider->extension = Vector2(width, height);
}

void PlayerObject::Init(std::string object_type, Alignment player_alignment, Type player_type)
{
	entity_ID = object_type;

	alignment = player_alignment;
	type = player_type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void PlayerObject::Update(float deltatime)
{
	current_animation->Update(deltatime);

	//Vertical movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(!created_projectile)
		{
			if(direction.x == 1)
			{
				SetCurrentAnimation(WALKRIGHT);
			}
			else
			{
				SetCurrentAnimation(WALKLEFT);
			}
		}
		position.y -= velocity*deltatime;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if(!created_projectile)
		{
			if(direction.x == 1)
			{
				SetCurrentAnimation(WALKRIGHT);
			}
			else
			{
				SetCurrentAnimation(WALKLEFT);
			}
		}
		position.y += velocity*deltatime;
	}

	//horizontal movement
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKLEFT);
		}
		position.x -= velocity*deltatime;
		direction.y = 0;
		direction.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKRIGHT);
		}
		position.x += velocity*deltatime;
		direction.y = 0;
		direction.x = 1;
	}
	else
	{
		if(!created_projectile)
		{
			if(direction.x == 1)
			{
				SetCurrentAnimation(IDLERIGHT);
			}
			else
			{
				SetCurrentAnimation(IDLELEFT);
			}
		}
	}

	if(created_projectile)
	{
		shooting_delay += deltatime;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		create_projectile = true;
		created_projectile = true;
		SetCurrentAnimation(ATTACKRIGHT);
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

	collider->position = position;
	current_animation->getSprite()->setPosition(position.x, position.y);
}

void PlayerObject::OnCollision(Type type, Vector2 offset, Alignment enemy_alignment)
{
	//shape.move(offset.x, offset.y);
	std::cout << "x" << offset.x << std::endl;
	std::cout << "y" << offset.y << std::endl;
	
}