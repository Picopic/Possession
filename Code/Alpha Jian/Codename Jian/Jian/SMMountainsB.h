//SMMountainsB.h

#pragma once
#include "stdafx.h"

class SMMountainsB
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMMountainsB(void);
	~SMMountainsB(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

