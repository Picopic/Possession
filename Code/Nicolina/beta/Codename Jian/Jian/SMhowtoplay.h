//SMhowtoplay.h

#pragma once
#include "stdafx.h"

class SMhowtoplay
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMhowtoplay(void);
	~SMhowtoplay(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};
