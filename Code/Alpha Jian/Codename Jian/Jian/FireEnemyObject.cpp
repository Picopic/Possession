//FireEnemyObject

#include "stdafx.h"

#include "FireEnemyObject.h"
//f�r randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>

FireEnemyObject::FireEnemyObject()
{
	
}

FireEnemyObject::FireEnemyObject(Vector2 enemy_position, int enemy_width, int enemy_height)
{
	velocity = Vector2(0,0);

	current_animation = nullptr;

	position = enemy_position;
	width = enemy_width;
	height = enemy_height;

	flagged_for_death = false;
	dead = false;

	hitpoints = 5;

	//shooting
	delay = 0.0f;
	shooting_delay = 0.001f;
	created_projectile = false;
	create_projectile = false;

	//collision
	entity_offset_x = 50;
	entity_offset_y = 40;
	can_collide = true;

	//movement
	speed = 200;
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

	//m_random = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
	m_random = (rand()%(500-(400)+1))+(400);

	//F�r att waterenemy ska spawna utanf�r rutan men g� till v�nster:
	velocity= Vector2(0, 0.2);
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
	//f�ljer efter spelaren i x-led
		if(position.x > player->getPosition().x + m_random){
			velocity.x = -0.1;
		}
	
		//ska f�lja efter spelarens y-postiion sakta
		if (position.y > player->getPosition().y + 100) {
			velocity.y = -0.15;
		}  
		//ska f�lja efter spelarens y-position sakta
		if (position.y < player -> getPosition().y - 100) {
			velocity.y = +0.15;
		}

		//Den ska stanna p� ett visst avst�nd i X-led:
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