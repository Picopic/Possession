//WoodEnemyObject.cpp

#include "stdafx.h"

#include "WoodEnemyObject.h"

WoodEnemyObject::WoodEnemyObject()
{}

WoodEnemyObject::WoodEnemyObject(ConfigManager* config_manager, Vector2 enemy_position)
{
	velocity = Vector2(0,0);

	Intercept = true;

	current_animation = nullptr;

	position = enemy_position;
	width = config_manager->ReadInt("woodwidth");
	height = config_manager->ReadInt("woodheight");

	flagged_for_death = false;
	dead = false;

	hitpoints = config_manager->ReadInt("woodhitpoints");

	//shooting
	delay = config_manager->ReadFloat("woodshootingdelay");
	shooting_delay = 0.001f;
	created_projectile = false;
	create_projectile = false;

	//lost soul
	drop_lostsoul = false;
	lostsouldrop_delay = 0.001f;
	lostsoulgoahead_delay = 1.0f;
	dropped_lostsoul  = false;
	random_number = (rand()%(7-(0)+1))+(0);

	//collision
	entity_offset_x = config_manager->ReadInt("woodoffsetx");
	entity_offset_y = config_manager->ReadInt("woodoffsety");
	can_collide = true;

	//movement
	speed = config_manager->ReadInt("woodmovementspeed");
	direction = Vector2(-1, 1);

	collision_refresh_timer = 0.0f;
	knockback_time = 0.2f;
	death_animation_time = 0.0f;
	movement_time = 0.0f;

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

	player = nullptr;
}

void WoodEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(500-(400)+1))+(400);
}

void WoodEnemyObject::Update(float deltatime)
{
	//Firstly update the animation
	current_animation->Update(deltatime);

	//Secondly update the sprites position if there is a collider
	if(hasCollider())
	{
		current_animation->getSprite()->setPosition(position.x, position.y);

		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
	}

	if(!dead)
	{
		if(!can_collide)
		{
			collision_refresh_timer += deltatime;
			//can collide again
			if(collision_refresh_timer > knockback_time)
			{
				can_collide = true;
				collision_refresh_timer = 0.0f;
			}
		}
		else
		{
			//Attacking
			if(created_projectile)
			{
				shooting_delay += deltatime;
				if(current_animation->GetCurrentFrame() == 4 && direction.x == 1)
				{
					float extension = 0.0f;
					extension = collider->extension.x;
					collider->position.x = (position.x + extension) + extension;
				}
					
				else if(current_animation->GetCurrentFrame() == 4 && direction.x == -1)
				{
					if(direction.x == -1)
						collider->position.x = collider->position.x - collider->extension.x;
					else if(direction.x == 1)
						collider->position.x = collider->position.x + collider->extension.x;
				}
					
			}

			Attack();

			if(shooting_delay > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
			{
				shooting_delay = 0.001f;
				created_projectile = false;
			}
			//end of attacking

			//Movement
			if(!created_projectile)
				Movement(deltatime);
		}
	}
	else
	{
		death_animation_time += deltatime;
		if(death_animation_time > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
		{
			flagged_for_death = true;
		}
		//drop lost soul delay
		if(dropped_lostsoul == true)
		{
			lostsouldrop_delay += deltatime;
		}

		if(lostsouldrop_delay == 0.001f && !dropped_lostsoul && random_number<=2)
		{
			drop_lostsoul = true;
			dropped_lostsoul = true;
		}
		else
		{
			drop_lostsoul = false;
		}

		if(lostsouldrop_delay > lostsoulgoahead_delay)
		{
			lostsouldrop_delay = 0.001f;
			dropped_lostsoul = false;
		}
	}

	if(hasCollider())
	{
		//Change the position of the hitbox
		hitbox.setPosition(collider->position.x, collider->position.y);
	}
	
}

void WoodEnemyObject::OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		if(enemy_type == WATER)
		{
			hitpoints--;
		}
		else if(enemy_type == FIRE)
		{
			hitpoints -= 3;
			can_collide = false;
		
			if(collision_entity->getDirection().x == 1 && current_animations_name != HITLEFT)
				SetCurrentAnimation(HITLEFT);
			else if(collision_entity->getDirection().x == -1 && current_animations_name != HITRIGHT)
				SetCurrentAnimation(HITRIGHT);
		}
		else if(enemy_type == WOOD)
		{
			hitpoints -= 2;
		}
	}
	else
	{

	}

	//Death
	if(hitpoints <= 0)
	{
		if(hasCollider())
		{
			delete collider;
			collider = nullptr;
		}
		dead = true;
		if(current_animations_name != DEATHLEFT)
			SetCurrentAnimation(DEATHLEFT);

		current_animation->getSprite()->setPosition(position.x, position.y);

		auto it = entity_sounds.find("DEATH");

		if(it != entity_sounds.end())
		{
			CurrentSound = it->second;
			CurrentSound->play();
		}
	}
}

void WoodEnemyObject::AddSounds(SoundManager* sound_mgr)
{
	entity_sounds.insert(std::pair<std::string, sf::Sound*>("DEATH", sound_mgr->Load("\Deaths/Wood Enemy Death.wav")));
}

//--------------------------AI FUNCTIONS--------------------------------//
void WoodEnemyObject::Movement(float Deltatime)
{
	float deltaY, deltaX, distance;
	
	if(Intercept)
	{
		deltaY = (position.y + (current_animation->getSprite()->getTextureRect().height -  height/2)) -
			(player->getPosition().y + player->GetOffsetY() + player->getHeight()/2);
		deltaX = (position.x + (current_animation->getSprite()->getTextureRect().width/2)) -
			(player->getPosition().x + player->GetCurrentAnimation()->getSprite()->getTextureRect().width + (collider->extension.x*3));

		if(deltaY < player->getHeight())
		{
			if(deltaX < collider->extension.x*3)
				Intercept = false;
			else if(deltaX > -(collider->extension.x*3))
				Intercept = false;
		}
		if(deltaY > -(player->getHeight()))
		{
			if(deltaX < collider->extension.x*3)
				Intercept = false;
			else if(deltaX > -(collider->extension.x*3))
				Intercept = false;
		}
	}
	else
	{
		deltaY = (position.y + (current_animation->getSprite()->getTextureRect().height -  height/2)) -			//Middle of wood enemy's hitbox y
			(player->getPosition().y + player->GetOffsetY() + player->getHeight()/2);							//Middle of players hitbox y
		deltaX = (position.x + current_animation->getSprite()->getTextureRect().width/2) -						//Middle of wood enemy's x
			(player->getPosition().x + player->GetCurrentAnimation()->getSprite()->getTextureRect().width/2);	//Middle of players x

		if(deltaY > player->getHeight()/2)
		{
			if(deltaX > collider->extension.x*3)
				Intercept = true;
			else if(deltaX < -(collider->extension.x*3))
				Intercept = true;
		}
	}

	distance = sqrtf((deltaY*deltaY)/3+deltaX*deltaX) * 3;

	//Set the direction
	if(deltaX > 0)
		direction.x = -1;
	else if(deltaX < 0)
		direction.x = 1;

	if(deltaY > 0)
		direction.y = -1;
	else if(deltaY < 0)
		direction.y = 1;

	velocity=Vector2((deltaX/distance)*-(speed * 3 * Deltatime), (deltaY/distance)*-((speed*4) * Deltatime));

	if(distance <= collider->extension.x)
	{
		//HIT
		velocity =Vector2(0, 0);
		if(direction.x == -1 && current_animations_name != IDLELEFT)
		{
			SetCurrentAnimation(IDLELEFT);
			direction.y = 0;
		}
		else if(direction.x == 1 && current_animations_name != IDLERIGHT)
		{
			SetCurrentAnimation(IDLERIGHT);
			direction.y = 0;
		}
	}
	else if(direction.x == -1 && current_animations_name != WALKLEFT)
	{
		SetCurrentAnimation(WALKLEFT);
	}
	else if(direction.x == 1 && current_animations_name != WALKRIGHT)
		SetCurrentAnimation(WALKRIGHT);

	position += velocity;
	
}

void WoodEnemyObject::Attack()
{
	if(shooting_delay == 0.001f && !created_projectile)
	{
		float distanceX = 500;
		float distanceY = 500;

		//X distance
		if(direction.x == 1)
		{
			distanceX = fabs((player->GetSprite()->getPosition().x + player->GetSprite()->getTextureRect().width/2)
				- (collider->position.x + collider->extension.x));
		}
		else if(direction.x == -1)
		{
			distanceX = fabs((player->GetSprite()->getPosition().x + player->GetSprite()->getTextureRect().width/2)
				- collider->position.x);
		}

		//Y distance
		distanceY = fabs((player->getPosition().y + player->GetOffsetY() + (player->getHeight()/2)) 
			- (collider->position.y + (height/2)));

		if(distanceX < collider->extension.x && !player->IsDead())
		{
			if(distanceY > -(height/2) && distanceY < (height/2))
			{
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
		}
	}
}

//--------------------------End of AI FUNCTIONS-------------------------//