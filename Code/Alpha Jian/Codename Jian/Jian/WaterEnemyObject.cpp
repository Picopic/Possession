//WaterEnemyObject.cpp

#include "stdafx.h"

#include "WaterEnemyObject.h"

WaterEnemyObject::WaterEnemyObject()
{

}

WaterEnemyObject::WaterEnemyObject(ConfigManager* config_mgr, Vector2 enemy_position)
{
	velocity = Vector2(0,0);

	current_animation = nullptr;

	position = enemy_position;
	width = config_mgr->ReadInt("waterwidth");
	height = config_mgr->ReadInt("waterheight");

	flagged_for_death = false;
	dead = false;

	hitpoints = config_mgr->ReadInt("waterhitpoints");

	//shooting
	delay = config_mgr->ReadFloat("watershootingdelay");
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
	entity_offset_x = config_mgr->ReadInt("wateroffsetx");
	entity_offset_y = config_mgr->ReadInt("wateroffsety");
	can_collide = true;

	//movement
	speed = config_mgr->ReadInt("watermovementspeed");
	direction = Vector2(-1, 1);

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

void WaterEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);

	//m_random = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
	m_random = (rand()%(500-(400)+1))+(400);
}

void WaterEnemyObject::Update(float deltatime)
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
	
	if(shooting_delay >= current_animation->GetNumberOfFrames() * current_animation->GetFrameDuration())
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
	if (position.y < player->getPosition().y - 100) {
		velocity.y = +0.15;
	}

	//Den ska stanna p� ett visst avst�nd i X-led:
	if (position.x < player->getPosition().x + m_random) {
		velocity.x = 0.1;
	}

	//Stop the movement
	if(position.y < player->getPosition().y + 50 && position.y > player->getPosition().y - 50){
		velocity.y = 0;
	}

	position += velocity;
	
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
		current_animation->getSprite()->setPosition(position.x, position.y);
		collider->position.x = position.x + entity_offset_x;
		collider->position.y = position.y + entity_offset_y;
		hitbox.setPosition(collider->position.x, collider->position.y);
	}
}

void WaterEnemyObject::OnCollision(Entity* collision_entity, Type enemy_type, Vector2 offset, Alignment enemy_alignment)
{
	if(enemy_alignment == FRIENDBULLET)
	{
		if(enemy_type == WOOD)
			{
				hitpoints -= 3;
			}
			else if(enemy_type == WATER)
			{
				hitpoints -= 2;
			}
			else if(enemy_type == FIRE)
			{
				hitpoints--;
			}
	}
	else if(enemy_alignment == PLAYER)
	{

	}
	
}