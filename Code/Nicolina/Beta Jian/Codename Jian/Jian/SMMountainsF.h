//SMMountainsF.h

#pragma once
#include "stdafx.h"

class SMMountainsF
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMMountainsF(void);
	~SMMountainsF(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

