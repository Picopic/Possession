//PlayerObject.cpp

#include "stdafx.h"

#include "PlayerObject.h"

PlayerObject::PlayerObject()
{

}

PlayerObject::PlayerObject(ConfigManager* Config_Manager)
{
	current_animation = nullptr;
	CurrentSound = nullptr;
	HitByWoodEnemy = false;
	WoodKnockbackSpeed = 5.0;

	//

	m_CanPickUp = true;

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

	//altars
	altar_counter = 0.0f;
	used_altar = false;

	//element change
	element_changed = false;
	element_changed_delay = 0.0f;
	change_delay = Config_Manager->ReadFloat("playerchangedelay");

	//HUD changing variables
	add_element = false;
	destroy_fire = 0;
	destroy_water = 0;
	destroy_wood = 0;
	addSoul = false;
	deleteSoul = false;

	//karma & sky colours
	karma = 0;
	red = 64;
	green = 32;
	blue = 48;

	//sounds
	isWalking = false;


	fire_elements = Config_Manager->ReadFloat("playerfire");
	water_elements = Config_Manager->ReadFloat("playerwater");
	wood_elements = Config_Manager->ReadFloat("playerwood");

	movement_time = 0.0f;
	speed = Config_Manager->ReadFloat("playerspeed");

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(collider->position.x, collider->position.y);
	hitbox.setFillColor(sf::Color(0,0,0,0));
	hitbox.setOutlineThickness(1);
	hitbox.setOutlineColor(sf::Color(255,0,0,255));
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
	//Reset the soul HUD change variables
	addSoul = false;
	deleteSoul = false;

	add_element = false;

	if(!dead)
	{
		//collision timer
		if(!can_collide)
		{
			collision_refresh_timer += deltatime;
			
			if(HitByWoodEnemy)
			{
				position.x += deltatime * knockback_speed * collision_direction.x * WoodKnockbackSpeed;
				position.y += deltatime * knockback_speed * collision_direction.y * WoodKnockbackSpeed;;
			}
			else
			{
				position.x += deltatime * knockback_speed * collision_direction.x;
				position.y += deltatime * knockback_speed * collision_direction.y;
			}

			//can collide again
			if(collision_refresh_timer > knockback_time)
			{
				can_collide = true;
				HitByWoodEnemy = false;
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
			if(shooting_delay == 0.001f || shooting_delay > 0.2)
			{
				if(!used_lost_souls)
				{
					//If you are not shooting, then you are able to move
					Movement(deltatime);

						//walk sound
					if(isWalking == true)
					{
						if(current_animations_name == WALKLEFT || current_animations_name == WALKRIGHT)
						{
							if(current_animation->GetCurrentFrame() == 0)
							{
								if(CurrentSound->getStatus() != sf::SoundSource::Playing)
								CurrentSound->play();
							}
						}
					}
					else
					{
						if(CurrentSound != nullptr)
							CurrentSound->stop();
					
					}

				}
				
				//If you are not shooting, then you are able to use souls
				Souls();

				//Elemental swap
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !element_changed && CanChangeElement())
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
				switch (type)
				{
				case FIRE:
					if(fire_elements == 10)
						Doubleshot = true;
					else
						Doubleshot = false;
					break;
				case WATER:
					if(water_elements == 10)
						Doubleshot = true;
					else
						Doubleshot = false;
					break;
				case WOOD:
					if(wood_elements == 10)
						Doubleshot = true;
					else
						Doubleshot = false;
					break;
				}

				create_projectile = true;
				created_projectile = true;
				if(direction.x == 1 && current_animations_name != ATTACKRIGHT)
				{
					SetCurrentAnimation(ATTACKRIGHT);
				}
				else if(direction.x == -1 && current_animations_name != ATTACKLEFT)
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

			//timern till lost souls
			if(used_lost_souls)
			{
				//Sound
				if(current_animations_name == EATLEFT || current_animations_name == EATRIGHT)
				{
					if(current_animation->GetCurrentFrame() == 2)
					{
						if(CurrentSound->getStatus() != sf::SoundSource::Playing)
							CurrentSound->play();
					}
				}

				if(current_animations_name == RELEASELEFT || current_animations_name == RELEASERIGHT)
				{
					if(current_animation->GetCurrentFrame() == 2)
					{
						if(CurrentSound->getStatus() != sf::SoundSource::Playing)
							CurrentSound->play();
					}
				}
				//End of sound

				lost_souls_counter += deltatime;
				if(lost_souls_counter > 0.5)
				{
					used_lost_souls = false;
					lost_souls_counter = 0.0f;
				}
			}

			//altare counter
			if(used_altar)
			{
				altar_counter += deltatime;
				if(altar_counter > 5.0)
				{
					used_altar = false;
					altar_counter = 0.0f;
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
		hitbox.setPosition(sf::Vector2f(collider->position.x, collider->position.y));
	}
	current_animation->getSprite()->setPosition(position.x, position.y);
	current_animation->Update(deltatime);
}

//COLLISION
void PlayerObject::OnCollision(Entity* collision_entity, Type collision_type, Vector2 offset, Alignment collision_alignment)
{
	if(collision_alignment == LOSTSOUL)
	{
		if(collectedSouls < 5)
		{
			collectedSouls++;
			hasLostSoul = true;
			addSoul = true;
			m_CanPickUp = true;
		}
		else
		{
			m_CanPickUp = false;
		}
	}
	else if(collision_alignment == ALTAR && !used_altar)
	{
		add_element = true;
		if(fire_elements <= 0)
		{
			fire_elements += 1;
			add_fire = 1;
			used_altar = true;
		}
		if(water_elements <= 0)
		{
			water_elements += 1;
			add_water = 1;
			used_altar = true;
		}
		if(wood_elements <= 0)
		{
			wood_elements += 1;		
			add_wood = 1;
			used_altar = true;
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

			HitByWoodEnemy = true;

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

		if(collision_entity->getDirection().x == 1 && current_animations_name != HITLEFT
			&& current_animations_name != DEATHLEFT && current_animations_name != DEATHRIGHT)
		{
			SetCurrentAnimation(HITLEFT);
			current_animations_name = HITLEFT;
		}
		else if(collision_entity->getDirection().x == -1 && current_animations_name != HITRIGHT
			&& current_animations_name != DEATHLEFT && current_animations_name != DEATHRIGHT)
		{
			SetCurrentAnimation(HITRIGHT);
			current_animations_name = HITRIGHT;
		}
			
	}
	if(collision_alignment == FIREFOEBULLET || collision_alignment == WATERFOEBULLET || collision_alignment == WOODFOEBULLET)
	{
		collision_direction = collision_entity->getDirection();
	}
	else
	{
		if(collision_alignment != WOODFOE)
		{
			collision_direction.x = -direction.x;
			collision_direction.y = -direction.y;
		}
		else
		{
			collision_direction = Vector2(-1, 0);
		}
		
	}
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
				if(current_animations_name != DEATHRIGHT)
					SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				if(current_animations_name != DEATHLEFT)
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
				if(current_animations_name != DEATHRIGHT)
					SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				if(current_animations_name != DEATHLEFT)
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
				if(current_animations_name != DEATHRIGHT)
					SetCurrentAnimation(DEATHRIGHT);
			}
			else
			{
				if(current_animations_name != DEATHLEFT)
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
			auto it = entity_sounds.find("EAT");

			if(it != entity_sounds.end())
			{
				CurrentSound = it->second;
			}

			add_element = true;
			collectedSouls--;
			deleteSoul = true;
			used_lost_souls = true;
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
			auto it = entity_sounds.find("FREE");

			if(it != entity_sounds.end())
			{
				CurrentSound = it->second;
			}

			add_element = true;
			collectedSouls--;
			used_lost_souls = true;
			deleteSoul = true;
		}
	}
}

void Entity::AddSounds(SoundManager* sound_mgr)
{
	//Example insert
	//entity_sounds.insert(std::pair<std::string, sf::Sound*>("ATTACK", sound_mgr->Load("wizhit.wav")));
	entity_sounds.insert(std::pair<std::string, sf::Sound*>("EAT", sound_mgr->Load("Sacrifice.wav")));
	entity_sounds.insert(std::pair<std::string, sf::Sound*>("FREE", sound_mgr->Load("Release.wav")));
	entity_sounds.insert(std::pair<std::string, sf::Sound*>("WALK", sound_mgr->Load("Walk_test.wav")));
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

void PlayerObject::Movement(float deltatime)
{
	//Vertical movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if((direction.x == 1) && current_animations_name != WALKRIGHT)
		{
			SetCurrentAnimation(WALKRIGHT);
		}
		else if((direction.x == -1) && current_animations_name != WALKLEFT)
		{
			SetCurrentAnimation(WALKLEFT);
		}
		
		position.y -= speed*deltatime;
		direction.y = -1;
		
		isWalking = true;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(direction.x == 1 && current_animations_name != WALKRIGHT)
		{
			SetCurrentAnimation(WALKRIGHT);
		}
		else if(direction.x == -1 && current_animations_name != WALKLEFT)
		{
			SetCurrentAnimation(WALKLEFT);
		}
		
		position.y += speed*deltatime;
		direction.y = 1;

		isWalking = true;
	}

	//horizontal movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(direction.x == -1 && current_animations_name != WALKLEFT)
		{
			SetCurrentAnimation(WALKLEFT);
		}
		
		position.x -= speed*deltatime;
		direction.x = -1;

		isWalking = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(current_animations_name != WALKRIGHT)
		{
			SetCurrentAnimation(WALKRIGHT);
		}

		position.x += speed*deltatime;
		direction.x = 1;

		isWalking = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(!used_lost_souls)
		{
			if(direction.x == 1 && current_animations_name != IDLERIGHT)
			{
				SetCurrentAnimation(IDLERIGHT);
				direction.y = 0;
			}
			else if(direction.x == -1 && current_animations_name != IDLELEFT)
			{
				SetCurrentAnimation(IDLELEFT);
				direction.y = 0;
			}

			isWalking = false;
		}
	}

	if (isWalking == true) {
		auto it = entity_sounds.find("WALK");

			if(it != entity_sounds.end())
			{
				CurrentSound = it->second;
			}
	}
}

void PlayerObject::Souls()
{
	//sacrifice lost soul
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hasLostSoul==true)
	{
		if(!used_lost_souls)
		{
			karma -= 2;
			blue -= 2;
			red += 10;
			SacrificeSoul(type);
			if(collectedSouls <= 0)
			{
				hasLostSoul = false;
			}

			if(direction.x == 1 && current_animations_name != EATRIGHT)
			{
				SetCurrentAnimation(EATRIGHT);
				current_animations_name = EATRIGHT;
			}
			else if(direction.x == -1 && current_animations_name != EATLEFT)
			{
				SetCurrentAnimation(EATLEFT);
				current_animations_name = EATLEFT;
			}
		}
	}
	//free lost soul
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && hasLostSoul==true)
	{
		if(!used_lost_souls)
		{
			karma ++;
			red -= 2;
			blue += 10;
			ReleaseSoul();
			if(collectedSouls <= 0)
			{
				hasLostSoul = false;
			}
			
			if(direction.x == 1 && current_animations_name  != RELEASERIGHT)
			{
				SetCurrentAnimation(RELEASERIGHT);
				current_animations_name = RELEASERIGHT;
			}
			else if(direction.x == -1 && current_animations_name != RELEASELEFT)
			{
				SetCurrentAnimation(RELEASELEFT);
				current_animations_name = RELEASELEFT;
			}
		}
	}
}

bool Entity::AddSoul()
{
	return addSoul;
}

bool Entity::DeleteSoul()
{
	return deleteSoul;
}

//colours
int Entity::getRed()
{
	return red;
}

void Entity::setRed(int newRed)
{
	red = newRed;
}

int Entity::getGreen()
{
	return green;
}

void Entity::setGreen(int newGreen)
{
	green = newGreen;
}

int Entity::getBlue()
{
	return blue;
}

void Entity::setBlue(int newBlue)
{
	blue = newBlue;
}