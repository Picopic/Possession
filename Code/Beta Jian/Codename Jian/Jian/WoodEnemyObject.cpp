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

	//enemy ai chase
	float deltaY = position.y - player->getPosition().y+120;
	float deltaX = position.x - player->getPosition().x-60;
	float distance = sqrt(deltaY*deltaY+deltaX*deltaX);

	velocity=Vector2((deltaX/distance)*-250, (deltaY/distance)*-50);

	if(distance<=150){
		velocity =Vector2(0, 0);
	}

	position+=velocity*deltatime;


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
		}
		else if(enemy_type == WOOD)
		{
			hitpoints -= 2;
		}
	}
	else
	{

	}
}
