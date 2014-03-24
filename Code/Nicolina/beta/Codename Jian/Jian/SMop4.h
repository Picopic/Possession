//SMop4.h

#pragma once
#include "stdafx.h"

class SMop4
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMop4(void);
	~SMop4(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};