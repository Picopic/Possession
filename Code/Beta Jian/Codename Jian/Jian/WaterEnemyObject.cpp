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

void WaterEnemyObject::Init(std::string object_type, Alignment enemy_alignment, Type enemy_type)
{
	alignment = enemy_alignment;
	type = enemy_type;

	current_animation->getSprite()->setPosition(position.x, position.y);

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(600-(500)+1))+(500);
}

void WaterEnemyObject::Update(float deltatime)
{
	//Firstly update the animation
	current_animation->Update(deltatime);

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
			//Attack
			if(created_projectile)
			{
				shooting_delay += deltatime;
			}

			Attack();

			if(shooting_delay > delay)
			{
				shooting_delay = 0.001f;
				created_projectile = false;
			}
	
	
			if(shooting_delay > current_animation->GetNumberOfFrames()*current_animation->GetFrameDuration())
			{
				if(direction.x == 1 && current_animations_name != IDLERIGHT)
				{
					SetCurrentAnimation(IDLERIGHT);
				}
				else if(direction.x == -1 && current_animations_name != IDLELEFT)
				{
					SetCurrentAnimation(IDLELEFT);
				}
			}
	

			//enemy ai chase
			float deltaY = position.y - player->getPosition().y+120;
			float deltaX = position.x - player->getPosition().x-60;
			float distance = sqrt(deltaY*deltaY+deltaX*deltaX);

			velocity=Vector2((deltaX/distance)*40, (deltaY/distance)*100);

			if(distance>=800){
				velocity =Vector2(0, 0);
				//if (deltaY>=-60 && deltaY <=60){
				//	if(position.y>=600){
				//	velocity.y = -140;
				//	}
				//	else if(position.y<=260){
				//	velocity.y=140;
				//	}
				//}
			}
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

	//position += velocity;

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

			can_collide = false;
		
			if(collision_entity->getDirection().x == 1 && current_animations_name != HITLEFT)
				SetCurrentAnimation(HITLEFT);
			else if(collision_entity->getDirection().x == -1 && current_animations_name != HITRIGHT)
				SetCurrentAnimation(HITRIGHT);
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

//----------------------AI FUNCTION------------------------//

void WaterEnemyObject::Attack()
{
	if(shooting_delay == 0.001f && !created_projectile)
	{
		create_projectile = true;
		created_projectile = true;
		if(current_animations_name != ATTACKLEFT)
			SetCurrentAnimation(ATTACKLEFT);
	}
	else
	{
		create_projectile = false;
	}
}

void WaterEnemyObject::Movement(float Deltatime)
{
	float deltaYUP = position.y - 240;
	float deltaYDOWN = 700 - position.y;

	if(deltaYDOWN < deltaYUP)
	{
		if(position.y < 700)
			position.y += speed * Deltatime;
		else if(position.y > 700)
			position.y -= speed * Deltatime;
	}
	else
	{
		if(position.y > 240)
			position.y -= speed * Deltatime;
		else if(position.y < 240)
			position.y += speed * Deltatime;
	}
}

//---------------------End of AI FUNCTION------------------//
