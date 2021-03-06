//SMoptions.h

#pragma once
#include "stdafx.h"
#include "AnimatedSprite.h"
#include "SMslider.h"


class SpriteManager;

class SMoptions
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture texture2;
	std::vector<AnimatedSprite*> sprite2;
	std::vector<AnimatedSprite*> sprite3;
	std::vector<AnimatedSprite*> sprite4;
	std::vector<AnimatedSprite*> sprite5;
	std::vector<AnimatedSprite> sprite6;

	SpriteManager* sprite_manager;

	float sprite_width, sprite_height;

public:
	SMoptions();
	~SMoptions(void);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);

	bool initialize(SpriteManager* spritemanager);

	SMslider* smslider1;
	SMslider* smslider2;
	SMslider* smslider3;
	//SMslider* onoff;
	//SMslider* vald;
	sf::Vector2f position;

	sf::Texture texture3;
	sf::Texture texture4;

	sf::Sprite fullscreenoption;
	sf::Sprite onoff;
	sf::Sprite vald;
};