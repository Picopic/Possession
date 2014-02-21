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

	//collision variables
	entity_offset_x = 50;
	entity_offset_y = 30;
	can_collide = true;
	collision_refresh_timer = 0.0f;

	//death
	dead = false;
	flagged_for_death = false;
	death_animation_time = 0.0f;

	//shooting
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = 0.01f;

	//lost souls
	collectedSouls = 0;
	hasLostSoul = false;

	//element change
	element_changed = false;
	element_changed_delay = 0.0f;

	//HUD changing variables
	add_element = false;
	destroy_fire = 0;
	destroy_water = 0;
	destroy_wood = 0;

	fire_elements = 3;
	water_elements = 3;
	wood_elements = 3;

	movement_time = 0.0f;
	speed = 200;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);
}

void PlayerObject::Init(std::string object_type, Alignment player_alignment, Type player_type)
{
	entity_ID = object_type;

	alignment = player_alignment;
	type = player_type;
	arrow = type;

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void PlayerObject::Update(float deltatime)
{
	changed_element = false;

	destroy_fire = 0;
	destroy_water = 0;
	destroy_wood = 0;
	add_fire = 0;
	add_water = 0;
	add_wood = 0;
	add_element = false;

	current_animation->Update(deltatime);

	add_element = false;

	if(!dead)
	{
		//collision timer
		if(!can_collide)
		{
			collision_refresh_timer += deltatime;
			
			//can collide again
			if(collision_refresh_timer > 0.3)
			{
				can_collide = true;
				collision_refresh_timer = 0.0f;
			}
		}

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
			position.y -= speed*deltatime;
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
			position.y += speed*deltatime;
		}

		//horizontal movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if(!created_projectile)
			{
				SetCurrentAnimation(WALKLEFT);
			}
			position.x -= speed*deltatime;
			direction.y = 0;
			direction.x = -1;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if(!created_projectile)
			{
				SetCurrentAnimation(WALKRIGHT);
			}
			position.x += speed*deltatime;
			direction.y = 0;
			direction.x = 1;
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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
			if(direction.x == 1)
			{
				SetCurrentAnimation(ATTACKRIGHT);
			}
			else
			{
				SetCurrentAnimation(ATTACKLEFT);
			}

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

		//adding elemental points (just a button press for testing)
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			//add_element = true;
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
			std::cout << "LostSouls: " << collectedSouls << "\n" << std::endl;
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
		std::cout << "LostSouls: " << collectedSouls << "\n" << std::endl;
		}
	}

	//death
	else
	{
		if(collider != nullptr)
		{
			delete collider;
			collider = nullptr;
		}
		death_animation_time += deltatime;
		if(death_animation_time > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
		{
			flagged_for_death = true;
		}
	}

	//Lastly update the collider and the sprites position
	if(hasCollider())
	{
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
	}
	current_animation->getSprite()->setPosition(position.x, position.y);
}

//COLLISION
void PlayerObject::OnCollision(Type collision_type, Vector2 offset, Alignment collision_alignment)
{
	can_collide = false;

	if (collision_alignment == FRIENDBULLET || collision_alignment == PLAYER)
	{

	}
	else if(collision_alignment == LOSTSOUL)
	{
		collectedSouls++;
		hasLostSoul = true;
	}
	else
	{
		switch (collision_type)
		{
		case FIRE:
			
			if(type == FIRE)
			{
				fire_elements -= 2;
				destroy_fire = 2;
				
				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements--;
				destroy_water = 1;

				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements -= 3;
				destroy_wood = 3;
				if(wood_elements <= 0) NextElement();
			}

			break;
		case WATER:

			if(type == FIRE)
			{
				fire_elements -= 3;
				destroy_fire = 3;

				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements -= 2;
				destroy_water = 2;

				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements--;
				destroy_wood = 1;

				if(wood_elements <= 0) NextElement();
			}

			break;
		case WOOD:

			if(type == FIRE)
			{
				fire_elements--;
				destroy_fire = 1;

				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements -= 3;
				destroy_water = 3;

				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements -= 2;
				destroy_wood = 2;

				if(wood_elements <= 0) NextElement();
			}

			break;
		}
	}

	
	
	std::cout << "Fire: " << fire_elements << std::endl;
	std::cout << "Water: " << water_elements << std::endl;
	std::cout << "Wood: " << wood_elements << std::endl;
	std::cout << "Souls: " << collectedSouls << "\n" << std::endl;

}

void PlayerObject::NextElement()
{
	changed_element = true;
	switch(type)
	{
	case FIRE:
		if(wood_elements > 0)
		{
			type = WOOD;
			arrow = WOOD;
		}
		else if(water_elements > 0)
		{
			type = WATER;
			arrow = WATER;
		}
		else
		{
			dead = true;
			if(direction.x == 1)
			{
				SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				SetCurrentAnimation(DEATHLEFT);
			}
		}
		
		break;
	case WATER:
		if(fire_elements > 0)
		{
			type = FIRE;
			arrow = FIRE;
		}
		else if(wood_elements > 0)
		{
			type = WOOD;
			arrow = WOOD;
		}
		else
		{
			dead = true;
			if(direction.x == 1)
			{
				SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				SetCurrentAnimation(DEATHLEFT);
			}
		}
		break;
	case WOOD:
		if(water_elements > 0)
		{
			type = WATER;
			arrow = WATER;
		}
		else if(fire_elements > 0)
		{
			type = FIRE;
			arrow = FIRE;
		}
		else
		{
			dead = true;
			if(direction.x == 1)
			{
				SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				SetCurrentAnimation(DEATHLEFT);
			}
		}
		break;
	}
}

bool Entity::AddElementPoints()
{
	return add_element;
}

bool Entity::DeleteElementPoints()
{
	if(destroy_fire > 0)
	{
		return true;
	}
	else if(destroy_water > 0)
	{
		return true;
	}
	else if(destroy_wood > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Entity::GetDestroyFire()
{
	return destroy_fire;
}

int Entity::GetDestroyWater()
{
	return destroy_water;
}

int Entity::GetDestroyWood()
{
	return destroy_wood;
}

int Entity::GetAddFire()
{
	return add_fire;
}

int Entity::GetAddWater()
{
	return add_water;
}

int Entity::GetAddWood()
{
	return add_wood;
}

Type Entity::GetArrow()
{
	return arrow;
}

bool Entity::ChangedElement()
{
	return changed_element;
}

void PlayerObject::SacrificeSoul(Type type)
{
	if(hasLostSoul==true) {
		add_element = true;
		if(type==WATER)
		{
			water_elements += 3;
			fire_elements += 1;
			wood_elements += 1;

			add_water = 3;
			add_fire = 1;
			add_wood = 1;
		}
		else if(type==FIRE)
		{
			water_elements += 1;
			fire_elements += 3;
			wood_elements += 1;

			add_fire = 3;
			add_water = 1;
			add_wood = 1;
		}
		else
		{
			water_elements += 1;
			fire_elements += 1;
			wood_elements += 3;

			add_wood = 3;
			add_fire = 1;
			add_water = 1;
		}
	}
}

void PlayerObject::ReleaseSoul() 
{
	if(hasLostSoul==true)
	{
		add_element = true;
		water_elements += 1;
		fire_elements += 1;
		wood_elements += 1;

		add_fire = 1;
		add_water = 1;
		add_wood = 1;
	}
}