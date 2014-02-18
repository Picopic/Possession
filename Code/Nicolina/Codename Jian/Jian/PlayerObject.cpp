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


	firePoints = 5;
	waterPoints = 5;
	woodPoints = 5;
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
	//Update the animation (switching frames etc)
	current_animation->Update(deltatime);

	//Vertical movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		current_animation->getSprite()->move(0, -velocity * deltatime);
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

		collider->position.y -= velocity * deltatime;
		position.y -= velocity*deltatime;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		current_animation->getSprite()->move(0, velocity * deltatime);
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
		

		collider->position.y += velocity*deltatime;
		position.y += velocity*deltatime;
	}
	//horizontal movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		current_animation->getSprite()->move(-velocity * deltatime, 0);
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKLEFT);
			current_animation->getSprite()->setPosition(position.x, position.y);
		}
		collider->position.x -= velocity*deltatime;
		position.x -= velocity*deltatime;
		direction.y = 0;
		direction.x = -1;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		current_animation->getSprite()->move(velocity * deltatime, 0);
		if(!created_projectile)
		{
			SetCurrentAnimation(WALKRIGHT);
			current_animation->getSprite()->setPosition(position.x, position.y);
		}
		collider->position.x += velocity*deltatime;
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

	if(enemy_alignment == WATERFOEBULLET)
	{
		if(type == WATER)
		{
			waterPoints -= 2;
		}
		else if(type == FIRE)
		{
			firePoints -= 3;
		}
		else if(type == WOOD)
		{
			woodPoints --;
		}
	}

	else if(enemy_alignment == FIREFOEBULLET)
	{
		if(type == WATER)
		{
			waterPoints --;
		}
		else if(type == FIRE)
		{
			firePoints -= 2;
		}
		else if(type == WOOD)
		{
			woodPoints -= 3;
		}
	}

	else if(enemy_alignment == WOODFOEBULLET)
	{
		if(type == WATER)
		{
			waterPoints -= 3;
		}
		else if(type == FIRE)
		{
			firePoints --;
		}
		else if(type == WOOD)
		{
			woodPoints -= 2;
		}
	}
	std::cout << "Water: " << waterPoints << std::endl;
	std::cout << "Fire: " << firePoints << std::endl;
	std::cout << "Wood: " << woodPoints << std::endl;
}

void PlayerObject::ElementalPoints(Type type)
{
	if(type==FIRE)
	{
		firePoints++;
	}
	else if(type==WATER)
	{
		waterPoints++;
	}
	else
	{
		woodPoints++;
	}
}