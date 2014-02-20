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

	//death
	dead = false;
	flagged_for_death = false;
	death_animation_time = 0.0f;

	//shooting
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = 0.01f;

	//element change
	element_changed = false;
	element_changed_delay = 0.0f;

	fire_elements = 1;
	water_elements = 1;
	wood_elements = 1;

	movement_time = 0.0f;
	velocity = 200;

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

	current_animation->getSprite()->setPosition(position.x, position.y);
}

void PlayerObject::Update(float deltatime, Entity* player) 
{
	current_animation->Update(deltatime);

	if(!dead)
	{
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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

void PlayerObject::OnCollision(Type collision_type, Vector2 offset, Alignment collision_alignment)
{
	if (collision_alignment == FRIENDBULLET || collision_alignment == PLAYER)
	{

	}
	else
	{
		switch (collision_type)
		{
		case FIRE:
			
			if(type == FIRE)
			{
				fire_elements -= 2;
				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements--;
				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements -= 3;
				if(wood_elements <= 0) NextElement();
			}

			break;
		case WATER:

			if(type == FIRE)
			{
				fire_elements -= 3;
				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements -= 2;
				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements--;
				if(wood_elements <= 0) NextElement();
			}

			break;
		case WOOD:

			if(type == FIRE)
			{
				fire_elements--;
				if(fire_elements <= 0) NextElement();
			}
			else if(type == WATER)
			{
				water_elements -= 3;
				if(water_elements <= 0) NextElement();
			}
			else if(type == WOOD)
			{
				wood_elements -= 2;
				if(wood_elements <= 0) NextElement();
			}

			break;
		}
	}
		
}

void PlayerObject::NextElement()
{
	switch(type)
	{
	case FIRE:
		if(wood_elements > 0)
		{
			type = WOOD;
		}
		else if(water_elements > 0)
		{
			type = WATER;
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
		}
		else if(wood_elements > 0)
		{
			type = WOOD;
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
		}
		else if(fire_elements > 0)
		{
			type = FIRE;
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