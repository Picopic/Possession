#pragma once
#include "stdafx.h"

class SpriteManager;
class AnimatedSprite;

class Gameplayarea
{
private:
	sf::Vector2f position;
	AnimatedSprite* sprite;


public:
	Gameplayarea(void);
	~Gameplayarea(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize(const std::string Background, SpriteManager* sprite_mgr);
};

