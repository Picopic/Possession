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

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(600-(500)+1))+(500);
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
	if (distance>=900){
		velocity=Vector2((deltaX/distance)*-100, (deltaY/distance)*-100);
	}

	position+=velocity*deltatime;

	if(position.y>=800){
		position.y=800;
	}
	if (position.y<=240){
		position.y=240;
	}

	////AI PLAYER CHASE


	////följer efter spelaren i x-led
	//if(position.x > player->getPosition().x + m_random){
	//	velocity.x = -0.1;
	//}

	////ska följa efter spelarens y-postiion sakta
	//if (position.y > player->getPosition().y + 200) {
	//	velocity.y = -0.3;
	//}  
	////ska följa efter spelarens y-position sakta
	//if (position.y < player -> getPosition().y - 200) {
	//	velocity.y = +0.3;
	//}

	//////ska undvika spelarens y-postiion snabbt
	////if (position.y <= player->getPosition().y + 10) {
	////	velocity.y = -0.5;
	////	//waterenemys collision med nedre kanten
	////	if (position.y>=1080){
	////		velocity.y = 0;
	////		position.y = 1080;
	////		//om spelaren också går ner till nedre kanten kommer waterenemy undivka uppåt
	////		if (player->getPosition().y<=1070){
	////			velocity.y = -0.5;
	////		}
	////	}
	////}  
	//////ska undvika spelarens y-position snabbt
	////if (position.y >= player->getPosition().y - 10) {
	////	velocity.y = +0.5;
	////	//waterenemys collision med horisontlinjen
	////	if (position.y<= 240){
	////		velocity.y = 0;
	////		position.y =240;
	////		//om spelaren också går till horisontlinjen kommer waterenemy undivka neråt
	////		if (player->getPosition().y>=230){
	////			velocity.y = +0.5;
	////		}
	////	}

	////Den ska stanna på ett visst avstånd i X-led:
	//if (position.x < player->getPosition().x + 800) {
	//	velocity.x = 0.1;
	//}

	////Stop the movement
	//if(position.y < player->getPosition().y + 50 && position.y > player->getPosition().y - 50){
	//	velocity.y = 0;
	//}

	//position += velocity;

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
