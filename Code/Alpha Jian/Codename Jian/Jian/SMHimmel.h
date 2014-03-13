//SMHimmel.h

#pragma once
#include "stdafx.h"

class SMHimmel
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMHimmel(void);
	~SMHimmel(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

