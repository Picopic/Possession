//AnimatedSprite.cpp

#include "stdafx.h"

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Texture* animation_spritesheet, int sprite_width, int sprite_height)
{
	time = 0.0f;
	current_frame = 0;
	x = 0;
	y = 0;
	width = sprite_width;
	height = sprite_height;
	spritesheet = animation_spritesheet;
	image = new sf::Sprite(*spritesheet, sf::IntRect(x, y, width, height));
}

void AnimatedSprite::Update(float deltatime)
{
	time += deltatime;
	if(time >= animation[current_frame].duration)
	{
		time = 0.0f;
		current_frame = ++current_frame  % animation.size();

		Frame &frame = animation[current_frame];
		x = frame.x;
		y = frame.y;
		width = frame.w;
		height = frame.h;

		image->setTextureRect(sf::IntRect(x, y, width, height));
	}
}

void AnimatedSprite::AddFrame(Frame &frame)
{
	animation.push_back(frame);
}

sf::Sprite* AnimatedSprite::getSprite()
{
	return image;
}

int AnimatedSprite::GetNumberOfFrames()
{
	return animation.size();
}

float AnimatedSprite::GetFrameDuration()
{
	return animation[0].duration;
}