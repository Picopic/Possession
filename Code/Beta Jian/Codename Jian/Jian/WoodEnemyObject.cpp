//WoodEnemyObject.cpp

#include "stdafx.h"

#include "WoodEnemyObject.h"

WoodEnemyObject::WoodEnemyObject()
{}

WoodEnemyObject::WoodEnemyObject(ConfigManager* config_manager, Vector2 enemy_position)
{
	velocity = Vector2(0,0);

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
	random_number = (rand()%(4-(0)+1))+(0);

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
	
		hitbox.setPosition(collider->position.x, collider->position.y);
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
					collider->position.x = collider->position.x - collider->extension.x;
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
	}
}

//--------------------------AI FUNCTIONS--------------------------------//
void WoodEnemyObject::Movement(float Deltatime)
{
	float deltaY = position.y - player->getPosition().y+120;
	float deltaX = position.x - player->getPosition().x-60;
	float distance = sqrt(deltaY*deltaY+deltaX*deltaX);

	velocity=Vector2((deltaX/distance)*-250, (deltaY/distance)*-50);

	if(distance <= player->GetCurrentAnimation()->getSprite()->getTextureRect().width){
	//HIT
	//velocity =Vector2(+60, 0);
	velocity =Vector2(0, 0);
	if(current_animations_name != IDLELEFT)
		SetCurrentAnimation(IDLELEFT);
	}
	else if(direction.x == -1 && current_animations_name != WALKLEFT)
	{
		SetCurrentAnimation(WALKLEFT);
	}
}

void WoodEnemyObject::Attack()
{
	if(shooting_delay == 0.001f && !created_projectile)
	{
		float distance = 500;

		if(direction.x == 1)
		{
			distance = fabs((player->GetSprite()->getPosition().x + player->GetSprite()->getTextureRect().width/2)
				- (current_animation->getSprite()->getPosition().x + current_animation->getSprite()->getTextureRect().width));
		}
		else if(direction.x == -1)
		{
			distance = fabs((player->GetSprite()->getPosition().x + player->GetSprite()->getTextureRect().width/2)
				- current_animation->getSprite()->getPosition().x);
		}

		if(distance < current_animation->getSprite()->getTextureRect().width/2)
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