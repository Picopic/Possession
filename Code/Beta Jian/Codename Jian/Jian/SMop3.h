//SMop3.h

#pragma once
#include "stdafx.h"

class SMop3
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMop3(void);
	~SMop3(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};