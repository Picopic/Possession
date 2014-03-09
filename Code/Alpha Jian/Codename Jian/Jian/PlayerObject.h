//PlayerObject.h

#pragma once
#include "Entity.h"

class PlayerObject : public Entity
{
public:
	PlayerObject();

	PlayerObject(ConfigManager* Config_Manager);

	//Initialise all the parameters
	void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type);
	void Update(float deltatime);
	void getID();
	void setID();

	void OnCollision(Entity* collision_entity, Type type, Vector2 offset, Alignment enemy_alignment);

	void SacrificeSoul(Type type);
	void ReleaseSoul();

	bool hasLostSoul;
	unsigned int collectedSouls;

	void NextElement();
	bool CanChangeElement();
private:
	//health
	int fire_elements;
	int water_elements;
	int wood_elements;

	//lost souls interaction
	float lost_souls_counter;
	bool used_lost_souls;

	//changing element
	bool element_changed;
	float element_changed_delay;
	float change_delay;

	//Collision
	float knockback_time;
	float knockback_speed;
	Vector2 collision_direction;
};