//FireEnemyObject

#include "stdafx.h"

#include "FireEnemyObject.h"
//för randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>

FireEnemyObject::FireEnemyObject()
{
	
}

FireEnemyObject::FireEnemyObject(ConfigManager* config_manager, Vector2 enemy_position)
{
	velocity = Vector2(0,0);

	current_animation = nullptr;

	position = enemy_position;
	width = config_manager->ReadInt("firewidth");
	height = config_manager->ReadInt("fireheight");

	flagged_for_death = false;
	dead = false;

	hitpoints = config_manager->ReadInt("firehitpoints");

	//shooting
	delay = config_manager->ReadFloat("fireshootingdelay");
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
	entity_offset_x = config_manager->ReadInt("fireoffsetx");
	entity_offset_y = config_manager->ReadInt("fireoffsety");
	can_collide = true;

	//movement
	speed = config_manager->ReadInt("firemovementspeed");
	direction = Vector2(-1, 1);

	death_animation_time = 0.0f;
	movement_time = 0.0f;

	collider = new Collider;
	collider->position.x = position.x + entity_offset_x;
	collider->position.y = position.y + entity_offset_y;
	collider->extension = Vector2(width, height);

	player = nullptr;

}

void FireEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);

	//HADE VILJAT HA MED DETTA PGA COLLISSION:
	//current_animation->getSprite()->setOrigin(current_animation->getSprite()->getLocalBounds().width/2, current_animation->getSprite()->getLocalBounds().height-(current_animation->getSprite()->getLocalBounds().height/10));

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(500-(400)+1))+(400);

	//För att waterenemy ska spawna utanför rutan men gå till vänster:
	//velocity= Vector2(0, 0.2);
}

void FireEnemyObject::Update(float deltatime)
{
	//Firstly update the animation
	current_animation->Update(deltatime);
	//movement
	if(current_animations_name != ATTACKLEFT || current_animations_name != ATTACKRIGHT)
	{
		//
		
		//
	}
	



	//Attack
	if(created_projectile)
	{
		shooting_delay += deltatime;
	}

	if(shooting_delay == 0.001f && !created_projectile)
	{
		create_projectile = true;
		created_projectile = true;
		SetCurrentAnimation(ATTACKLEFT);
		current_animations_name = ATTACKLEFT;
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
	
	if(shooting_delay > current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
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

	//AI PLAYER CHASE
	//följer efter spelaren i x-led
		if(position.x > player->getPosition().x + m_random){
			velocity.x = -0.1;
		}
	
		//ska följa efter spelarens y-postiion sakta
		if (position.y > player->getPosition().y + 100) {
			velocity.y = -0.15;
		}  
		//ska följa efter spelarens y-position sakta
		if (position.y < player -> getPosition().y - 100) {
			velocity.y = +0.15;
		}

		//Den ska stanna på ett visst avstånd i X-led:
		if (position.x < player->getPosition().x + m_random) {
			velocity.x = 0.1;
		}

		if(position.y < player ->getPosition().y + 50 && position.y > player ->getPosition().y - 50){
			velocity.y = 0;
		}

		position += velocity;

	//MOVEMENT UPP OCH NER
	/*if (position.y > 450){
		position.y = 450;
		velocity *= -1;

	}
	if (position.y < 200){
		position.y = 200;
		velocity *= -1;

	}

	position.x += speed*deltatime*velocity.x;
	position.y += speed*deltatime*velocity.y;*/

	//Death

	if(hitpoints <= 0)
	{
		if(hasCollider())
		{
			delete collider;
			collider = nullptr;
		}
		dead = true;
		SetCurrentAnimation(DEATHLEFT);
		current_animations_name = DEATHLEFT;
		current_animation->getSprite()->setPosition(position.x, position.y);
	}
	if(dead)
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

	//Lastly update the sprites position if there is a collider
	if(hasCollider())
	{
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
		current_animation->getSprite()->setPosition(position.x, position.y);
	}

}

void FireEnemyObject::OnCollision(Type enemy_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		if(enemy_type == WATER)
		{
			hitpoints -= 3;
		}
		else if(enemy_type == FIRE)
		{
			hitpoints -= 2;
		}
		else if(enemy_type == WOOD)
		{
			hitpoints--;
		}
	}
	else
	{
		
	}
	
}

void Entity::setplayer(Entity* p_player){
	player = p_player;
}