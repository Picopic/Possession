//Entity.h

#pragma once
#include "Collider.h"
#include <iostream>
#include "Enums.h"
#include "AnimatedSprite.h"
#include "SoundManager.h"

class Entity
{
public:
	Entity();
	Entity(Vector2 entity_position, int entity_width, int entity_height);
	virtual void Init(std::string object_type, Alignment alignment, Type type) = 0; //initiate the object
	virtual void Update(float deltatime, Entity* player) = 0; //apply logic to object
	void Cleanup();

	std::string getID();
	void setID(std::string new_ID);

	Alignment getAlignment();
	Collider* getCollider();
	Vector2 getPosition();
	bool hasCollider() const;
	Type getType();

	Vector2 getDirection();

	bool CreateProjectile();
	float getShootDelay();
	float getDelay();
	void setDelay(float new_delay);

	bool IsFlaggedForDeath();

	int getWidth();
	int getHeight();

	void AddAnimation(AnimationName animation_name, AnimatedSprite* anim_sprite);
	AnimatedSprite* GetCurrentAnimation();
	AnimationName GetCurrentAnimationsName();

	virtual void OnCollision(Type collision_type, Vector2 offset, Alignment enemy_alignment);

	sf::RectangleShape shape;

	//Sounds
	void AddSounds(SoundManager* sound_mgr);
protected:
	Collider *collider;
	Vector2 position;

	Alignment alignment;
	Type type;

	int width;
	int height;

	//health for enemies
	int hitpoints;

	std::string entity_ID;

	bool flagged_for_death;
	bool dead;

	//projectilehandling
	bool create_projectile;
	bool created_projectile;
	int max_projectile_count;
	float shooting_delay;
	float delay;
	Vector2 direction;

	//Collisionbox
	float entity_offset_x;
	float entity_offset_y;

	//movement
	float movement_time;
	float velocity;

	//Animations
	AnimatedSprite* current_animation;
	AnimationName current_animations_name;
	std::map<AnimationName, AnimatedSprite*> animations;
	float death_animation_time;
	void SetCurrentAnimation(AnimationName animation_name);

	//Sound
	std::map<std::string, sf::Sound*> entity_sounds;
};