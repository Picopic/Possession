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

	entity_offset_x = 50;
	entity_offset_y = 30;

	//shooting
	flagged_for_death = false;
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = 0.01f;

	//element change
	element_changed = false;
	element_changed_delay = 0.0f;

	movement_time = 0.0f;
	velocity = 200;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

	//Lost souls & elemental points

	collectedSouls = 0;
	hasLostSoul = false;

	soulChoiceSacrifice = false;
	soulChoiceFree = false;

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

	//Shooting
	if(created_projectile)
	{
		shooting_delay += deltatime;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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

	//end of shooting

	//Elemental swap
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !element_changed)
	{
		element_changed = true;

		NextElement();
	}
	if(element_changed)
	{
		element_changed_delay += deltatime;
		if(element_changed_delay > 0.5f)
		{
			element_changed = false;
			element_changed_delay = 0.0f;
		}
	}


	//sacrifice lost soul
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && hasLostSoul==true)
	{
		SacrificeSoul(type);
		collectedSouls--;
		if(collectedSouls <= 0)
		{
			hasLostSoul = false;
		}

	std::cout << "SACRIFICE!" << std::endl;
	std::cout << "Water: " << waterPoints << std::endl;
	std::cout << "Fire: " << firePoints << std::endl;
	std::cout << "Wood: " << woodPoints << std::endl;
	std::cout << "LostSouls: " << collectedSouls << std::endl;
	std::cout << " " << std::endl;
	}
	//free lost soul
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hasLostSoul==true)
	{
		ReleaseSoul();
		collectedSouls--;
		if(collectedSouls <= 0)
		{
			hasLostSoul = false;
		}
	std::cout << "RELEASE!" << std::endl;
	std::cout << "Water: " << waterPoints << std::endl;
	std::cout << "Fire: " << firePoints << std::endl;
	std::cout << "Wood: " << woodPoints << std::endl;
	std::cout << "LostSouls: " << collectedSouls << std::endl;
	std::cout << " " << std::endl;
	}

	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	current_animation->getSprite()->setPosition(position.x, position.y);
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

	if(enemy_alignment == LOSTSOUL)
	{
		collectedSouls++;
		hasLostSoul = true;
	}	

	std::cout << "COLLISION!" << std::endl;
	std::cout << "Water: " << waterPoints << std::endl;
	std::cout << "Fire: " << firePoints << std::endl;
	std::cout << "Wood: " << woodPoints << std::endl;
	std::cout << "LostSouls: " << collectedSouls << std::endl;
	std::cout << " " << std::endl;
}

void PlayerObject::SacrificeSoul(Type type)
{
	if(type==WATER)
	{
		waterPoints += 3;
		firePoints++;
		woodPoints++;
	}
	else if(type==FIRE)
	{
		waterPoints++;
		firePoints += 3;
		woodPoints++;
	}
	else
	{
		waterPoints++;
		firePoints++;
		woodPoints += 3;
	}
}

void PlayerObject::ReleaseSoul() 
{
	if(hasLostSoul==true)
	{
		waterPoints++;
		firePoints++;
		woodPoints++;
	}
}

void PlayerObject::NextElement()
{
	switch(type)
	{
	case FIRE:
		type = WOOD;
		break;
	case WATER:
		type = FIRE;
		break;
	case WOOD:
		type = WATER;
		break;
	}
}