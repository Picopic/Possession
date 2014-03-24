//SMMoon.h

#pragma once
#include "stdafx.h"

class SMMoon
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMMoon(void);
	~SMMoon(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

