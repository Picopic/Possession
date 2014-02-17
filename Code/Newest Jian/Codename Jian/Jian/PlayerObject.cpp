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
		current_animation->getSprite()->move(0, -200 * deltatime);
		if(!created_projectile)
		{
			if(direction.x == 1)
			{
				SetCurrentAnimation(WALKRIGHT);
				current_animation->getSprite()->setPosition(position.x, position.y);
			}
			else
			{
				SetCurrentAnimation(WALKLEFT);
				current_animation->getSprite()->setPosition(position.x, position.y);
			}
		}

		collider->position.y -= 200 * deltatime;
		position.y -= 200*deltatime;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		current_animation->getSprite()->move(0, 200 * deltatime);
		if(!created_projectile)
		{
			if(direction.x == 1)
			{
				SetCurrentAnimation(WALKRIGHT);
				current_animation->getSprite()->setPosition(position.x, position.y);
			}
			else
			{
				SetCurrentAnimation(WALKLEFT);
				current_animation->getSprite()->setPosition(position.x, position.y);
			}
		}
		

		collider->position.y += 200*deltatime;
		position.y += 200*deltatime;
	}
	//horizontal movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		current_animation->getSprite()->move(-200 * deltatime, 0);
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKLEFT);
			current_animation->getSprite()->setPosition(position.x, position.y);
		}
		collider->position.x -= 200*deltatime;
		position.x -= 200*deltatime;
		direction.y = 0;
		direction.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		current_animation->getSprite()->move(200 * deltatime, 0);
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKRIGHT);
			current_animation->getSprite()->setPosition(position.x, position.y);
		}
		collider->position.x += 200*deltatime;
		position.x += 200*deltatime;
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
			
			current_animation->getSprite()->setPosition(position.x, position.y);
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
		current_animation->getSprite()->setPosition(position.x, position.y);
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

void PlayerObject::OnCollision(Type type, Vector2 offset, Alignment enemy_alignment)
{
	//shape.move(offset.x, offset.y);
	std::cout << "x" << offset.x << std::endl;
	std::cout << "y" << offset.y << std::endl;
	
}