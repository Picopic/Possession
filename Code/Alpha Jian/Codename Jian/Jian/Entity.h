//Entity.h

#pragma once
#include "Collider.h"
#include <iostream>
#include "Enums.h"
#include "AnimatedSprite.h"
#include "SoundManager.h"
#include "ConfigManager.h"

class Entity
{
public:
	Entity();

	virtual void Init(std::string object_type, Alignment enemy_alignment, Type enemy_type) = 0; //initiate the object
	
	virtual void Update(float deltatime) = 0; //apply logic to object
	void Cleanup();

	//HUD changing functions
	bool AddElementPoints();
	bool DeleteElementPoints();
	int GetAddFire();
	int GetAddWater();
	int GetAddWood();
	int GetDestroyFire();
	int GetDestroyWater();
	int GetDestroyWood();
	Type GetArrow();
	bool ChangedElement();

	//For EnemyAI and assosiated
	void setplayer(Entity* p_player);

	//unorganised
	Alignment getAlignment();
	Collider* getCollider();
	Vector2 getPosition();
	void setPosition(Vector2 pos);
	Type getType();
	
	//collision
	bool hasCollider() const;
	bool CanCollide();

	Vector2 getDirection();

	//Shooting
	bool CreateProjectile();
	float getShootDelay();
	float getDelay();
	void setDelay(float new_delay);
	void resetShootDelay();

	//death
	bool IsFlaggedForDeath();

	//access
	int getWidth();
	int getHeight();
	sf::Sprite* GetSprite();
	sf::RectangleShape GetHitbox();

	//animations
	void AddAnimation(AnimationName animation_name, AnimatedSprite* anim_sprite);
	AnimatedSprite* GetCurrentAnimation();
	AnimationName GetCurrentAnimationsName();

	//Collision
	virtual void OnCollision(Entity* collision_entity,Type collision_type, Vector2 offset, Alignment enemy_alignment);

	//Sounds
	void AddSounds(SoundManager* sound_mgr);

	//Lost Souls
	bool GetLostSoul();

	//Enemy AI to not stack on each others
	void DontStack();
	void SetPositions(Vector2 p_position);
	void ClearPositions();

protected:
	Collider *collider;

	//Start position
	Vector2 position;

	Alignment alignment;
	Type type;

	int width;
	int height;

	int hitpoints;

	bool flagged_for_death;
	bool dead;

	int m_random;

	//Enemy variables
	Entity* player;

	//projectilehandling
	bool create_projectile;
	bool created_projectile;
	int max_projectile_count;
	float shooting_delay;
	float delay;
	Vector2 direction;
	Vector2 start_pos;

	//Collisionbox
	float entity_offset_x;
	float entity_offset_y;
	bool can_collide;
	float collision_refresh_timer;
	sf::RectangleShape hitbox;

	//movement
	float movement_time;
	float speed;
	Vector2 velocity;

	//HUD changes
	bool add_element;
	int add_fire;
	int add_water;
	int add_wood;
	int destroy_fire;
	int destroy_water;
	int destroy_wood;
	Type arrow;
	bool changed_element;

	//Animations
	AnimatedSprite* current_animation;
	AnimationName current_animations_name;
	std::map<AnimationName, AnimatedSprite*> animations;
	float death_animation_time;
	void SetCurrentAnimation(AnimationName animation_name);
	
	//Sound
	std::map<std::string, sf::Sound*> entity_sounds;

	//Lost Souls
	bool drop_lostsoul;
	float lostsouldrop_delay;
	float lostsoulgoahead_delay;
	bool dropped_lostsoul;
	int random_number;

	//Enemy AI to not stack on each other
	std::vector<Vector2> othersposition;

};