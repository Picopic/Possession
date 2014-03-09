//PlayerObject.cpp

#include "stdafx.h"

#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

}

PlayerObject::PlayerObject(ConfigManager* Config_Manager)
{
	current_animation = nullptr;

	//

	direction = Vector2(Config_Manager->ReadInt("playerdirx"), Config_Manager->ReadInt("playerdiry"));

	changed_element = false;

	position = Vector2(Config_Manager->ReadInt("playerx"), Config_Manager->ReadInt("playery"));
	width = Config_Manager->ReadInt("playerwidth");
	height = Config_Manager->ReadInt("playerheight");

	//collision variables
	entity_offset_x = Config_Manager->ReadFloat("playeroffsetx");
	entity_offset_y = Config_Manager->ReadFloat("playeroffsety");
	can_collide = true;
	collision_refresh_timer = 0.0f;
	knockback_time = Config_Manager->ReadFloat("playerknockbacktime");
	knockback_speed = Config_Manager->ReadFloat("playerknockbackspeed");

	//death
	dead = false;
	flagged_for_death = false;
	death_animation_time = 0.0f;

	//shooting
	create_projectile = false;
	created_projectile = false;
	shooting_delay = 0.001f;
	delay = Config_Manager->ReadFloat("playershootdelay");

	//lost souls
	collectedSouls = 0;
	hasLostSoul = false;
	lost_souls_counter = 0.0f;
	used_lost_souls = false;

	//element change
	element_changed = false;
	element_changed_delay = 0.0f;
	change_delay = Config_Manager->ReadFloat("playerchangedelay");

	//HUD changing variables
	add_element = false;
	destroy_fire = 0;
	destroy_water = 0;
	destroy_wood = 0;

	fire_elements = Config_Manager->ReadFloat("playerfire");
	water_elements = Config_Manager->ReadFloat("playerwater");
	wood_elements = Config_Manager->ReadFloat("playerwood");

	movement_time = 0.0f;
	speed = Config_Manager->ReadFloat("playerspeed");

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);
}

void PlayerObject::Init(std::string object_type, Alignment entity_alignment, Type entity_type)
{
	alignment = entity_alignment;
	type = entity_type;
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
			
			position.x += deltatime * knockback_speed * collision_direction.x;

			//can collide again
			if(collision_refresh_timer > knockback_time)
			{
				can_collide = true;
				collision_refresh_timer = 0.0f;
			}
		}
		else
		{
			//Shooting
			if(created_projectile)
			{
				shooting_delay += deltatime;
			}
			else
			{
				//If you are not shooting, then you are able to move
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

				//Elemental swap
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !element_changed && CanChangeElement())
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

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !created_projectile)
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

			

			//adding elemental points (just a button press for testing)
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				//add_element = true;
			}

			//sacrifice lost soul
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && hasLostSoul==true)
			{
				if(!used_lost_souls)
				{
					SacrificeSoul(type);
					if(collectedSouls <= 0)
					{
						hasLostSoul = false;
					}

					used_lost_souls = true;
					std::cout << "SACRIFICE!" << std::endl;
					std::cout << "LostSouls: " << collectedSouls << "\n" << std::endl;
				}
			}
			//free lost soul
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hasLostSoul==true)
			{
				if(!used_lost_souls)
				{
					ReleaseSoul();
					if(collectedSouls <= 0)
					{
						hasLostSoul = false;
					}

					used_lost_souls = true;
					std::cout << "RELEASE!" << std::endl;
					std::cout << "LostSouls: " << collectedSouls << "\n" << std::endl;
				}
			
			}

			//timern till lost souls
			if(used_lost_souls)
			{
				lost_souls_counter += deltatime;
				if(lost_souls_counter > 0.3)
				{
					used_lost_souls = false;
					lost_souls_counter = 0.0f;
				}
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

//COLLISION
void PlayerObject::OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment collision_alignment)
{
	if(collision_alignment == LOSTSOUL)
	{
		collectedSouls++;
		hasLostSoul = true;
	}
	else if(collision_alignment == ALTAR)
	{
		add_element = true;
		if(fire_elements <= 0)
		{
			fire_elements += 1;
			add_fire = 1;
		}
		if(water_elements <= 0)
		{
			water_elements += 1;
			add_water = 1;
		}
		if(wood_elements <= 0)
		{
			wood_elements += 1;		
			add_wood = 1;
		}
	}
	else if(collision_alignment == WALL)
	{
		can_collide = false;
	}
	else
	{
		can_collide = false;
		switch (collision_type)
		{
		case FIRE:
			
			if(type == FIRE)
			{
				fire_elements -= 2;
				destroy_fire = 2;
				
				if(fire_elements <= 0)
				{
					NextElement();
					fire_elements = 0;
				}
			}
			else if(type == WATER)
			{
				water_elements--;
				destroy_water = 1;

				if(water_elements <= 0)
				{
					NextElement();
					water_elements = 0;
				}
			}
			else if(type == WOOD)
			{
				wood_elements -= 3;
				destroy_wood = 3;
				if(wood_elements <= 0)
				{
					NextElement();
					wood_elements = 0;
				}
			}

			break;
		case WATER:

			if(type == FIRE)
			{
				fire_elements -= 3;
				destroy_fire = 3;

				if(fire_elements <= 0)
				{
					NextElement();
					fire_elements = 0;
				}
			}
			else if(type == WATER)
			{
				water_elements -= 2;
				destroy_water = 2;

				if(water_elements <= 0)
				{
					NextElement();
					water_elements = 0;
				}
			}
			else if(type == WOOD)
			{
				wood_elements--;
				destroy_wood = 1;

				if(wood_elements <= 0)
				{
					NextElement();
					wood_elements = 0;
				}
			}

			break;
		case WOOD:

			if(type == FIRE)
			{
				fire_elements--;
				destroy_fire = 1;

				if(fire_elements <= 0)
				{
					NextElement();
					fire_elements = 0;
				}
			}
			else if(type == WATER)
			{
				water_elements -= 3;
				destroy_water = 3;

				if(water_elements <= 0)
				{
					NextElement();
					water_elements = 0;
				}
			}
			else if(type == WOOD)
			{
				wood_elements -= 2;
				destroy_wood = 2;

				if(wood_elements <= 0)
				{
					NextElement();
					wood_elements = 0;
				}
			}

			break;
		}
	}

	collision_direction = collision_entity->getDirection();
	
	
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
		if(water_elements > 0)
		{
			type = WATER;
			arrow = WATER;
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
	case WATER:
		if(wood_elements > 0)
		{
			type = WOOD;
			arrow = WOOD;
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
	case WOOD:
		if(fire_elements > 0)
		{
			type = FIRE;
			arrow = FIRE;
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
	int added_points = 0;
	if(hasLostSoul==true) {
		if(type==WATER)
		{
			if(water_elements + 3 >= 10)
			{
				add_water = abs(water_elements - 10);
				added_points += abs(water_elements - 10);
				water_elements = 10;
				if(fire_elements + 1 >10){}
				else
				{
					added_points++;
					fire_elements++;
					add_fire = 1;
				}
				if(wood_elements + 1 >10){}
				else
				{
					added_points++;
					wood_elements++;
					add_wood = 1;
				}
			}
			else
			{
				added_points += 3;
				add_water = 3;
				water_elements += 3;
				if(fire_elements + 1 >10){}
				else
				{
					added_points++;
					fire_elements++;
					add_fire = 1;
				}
				if(wood_elements + 1 >10){}
				else
				{
					added_points++;
					wood_elements++;
					add_wood = 1;
				}
			}
		}
		else if(type==FIRE)
		{
			if(fire_elements + 3 >= 10)
			{
				add_fire = abs(fire_elements - 10);
				added_points += abs(fire_elements - 10);
				fire_elements = 10;
				if(water_elements + 1 >10){}
				else
				{
					added_points++;
					water_elements++;
					add_water = 1;
				}
				if(wood_elements + 1 >10){}
				else
				{
					added_points++;
					wood_elements++;
					add_wood = 1;
				}
			}
			else
			{
				added_points += 3;
				add_fire = 3;
				fire_elements += 3;
				if(water_elements + 1 >10){}
				else
				{
					added_points++;
					water_elements++;
					add_water = 1;
				}
				if(wood_elements + 1 >10){}
				else
				{
					added_points++;
					wood_elements++;
					add_wood = 1;
				}
			}
		}
		else
		{
			if(wood_elements + 3 >= 10)
			{
				add_wood = abs(wood_elements - 10);
				added_points += abs(wood_elements - 10);
				wood_elements = 10;
				if(fire_elements + 1 >10){}
				else
				{
					added_points++;
					fire_elements++;
					add_fire = 1;
				}
				if(water_elements + 1 >10){}
				else
				{
					added_points++;
					water_elements++;
					add_water = 1;
				}
			}
			else
			{
				added_points += 3;
				add_wood = 3;
				wood_elements += 3;
				if(fire_elements + 1 >10){}
				else
				{
					added_points++;
					fire_elements++;
					add_fire = 1;
				}
				if(water_elements + 1 >10){}
				else
				{
					added_points++;
					water_elements++;
					add_water = 1;
				}
			}
		}

		if(added_points > 0)
		{
			add_element = true;
			collectedSouls--;
		}
			
	}
}

void PlayerObject::ReleaseSoul() 
{
	if(hasLostSoul==true)
	{
		int added_points = 0;

		if(water_elements + 1 >10){}
		else
		{
			added_points++;
			water_elements++;
			add_water = 1;
		}
		if(fire_elements + 1 >10){}
		else
		{
			added_points++;
			fire_elements++;
			add_fire = 1;
		}
		if(wood_elements + 1 >10){}
		else
		{
			added_points++;
			wood_elements++;
			add_wood = 1;
		}

		if(added_points > 0)
		{
			add_element = true;
			collectedSouls--;
		}
	}
}

void Entity::AddSounds(SoundManager* sound_mgr)
{
	//Example insert
	//entity_sounds.insert(std::pair<std::string, sf::Sound*>("ATTACK", sound_mgr->Load("wizhit.wav")));
}

bool PlayerObject::CanChangeElement()
{
	switch (type)
	{
	case FIRE:
		if(water_elements <= 0 && wood_elements <= 0)
			return false;
		break;
	case WATER:
		if(wood_elements <= 0 && fire_elements <= 0)
			return false;
		break;
	case WOOD:
		if(water_elements <= 0 && fire_elements <= 0)
			return false;
		break;
	}

	return true;
}