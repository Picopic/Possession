//Paralax3.h
//Gräs i förgrunden

#pragma once
#include "stdafx.h"

class Paralax3

{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Paralax3(void);
	~Paralax3(void);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();

	void moveX(float x);
};
