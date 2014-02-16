#pragma once
#include "stdafx.h"

class Gameplayarea
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	Gameplayarea(void);
	~Gameplayarea(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

