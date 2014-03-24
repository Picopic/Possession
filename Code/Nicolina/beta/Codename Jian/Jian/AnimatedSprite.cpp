//AnimatedSprite.cpp

#include "stdafx.h"

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite(sf::Texture* animation_spritesheet, int sprite_width, int sprite_height, int texture_x, int texture_y)
{
	time = 0.0f;
	current_frame = 0;
	x = texture_x;
	y = texture_y;
	width = sprite_width;
	height = sprite_height;
	spritesheet = animation_spritesheet;
	PlayAnimation = true;
	image = new sf::Sprite(*spritesheet, sf::IntRect(x, y, width, height));
}

void AnimatedSprite::Update(float deltatime)
{
	time += deltatime;
	if(PlayAnimation)
	{
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

bool AnimatedSprite::IsLastFrame()
{
	if(current_frame % animation.size() == 0)
	{
		return true;
	}
	else
		return false;
}

void AnimatedSprite::StopAnimation()
{
	PlayAnimation = false;
}

void AnimatedSprite::StartAnimation()
{
	PlayAnimation = true;
}

int AnimatedSprite::GetCurrentFrame()
{
	return current_frame;
}

void AnimatedSprite::SetCurrentFrame(int frame)
{
	if(frame >= 0 && frame < animation.size())
		current_frame = frame;
	else
		std::cout << "The frame specified does not exist" << std::endl;
}