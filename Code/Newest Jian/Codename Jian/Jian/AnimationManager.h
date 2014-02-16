//AnimationManager.h

#pragma once

#include "Spritemanager.h"
#include "Animation.h"
#include "Enums.h"
#include <iostream>

class AnimationManager
{
public:
	AnimationManager();

	void Init(Alignment alignment);
	
	void LoadAnimations();
	//Get an animation approriate to the animation name, for example "WALK" or "ATTACK"
	sf::Sprite GetCurrentSprite();
	void UpdateAnimation(float deltatime);
	void SetAnimation(AnimationName next_animation);
	AnimationName GetAnimationName();

private:
	Alignment alignment;
	std::map<std::pair<AnimationName, Alignment>, Animation*>animations;
	AnimationName current_animation;
	float frame_time;
	float time_since_last_frame;
};