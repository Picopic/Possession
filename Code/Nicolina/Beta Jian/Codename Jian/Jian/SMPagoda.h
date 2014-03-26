//SMPagoda.h

#pragma once
#include "stdafx.h"

class SMPagoda
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;


public:
	SMPagoda(void);
	~SMPagoda(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};

