//SMpaused.h
//innehåller 2 bilder

#pragma once
#include "stdafx.h"

class SMpaused
{
private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Sprite sprite;
	sf::Sprite sprite2;

public:
	SMpaused(void);
	~SMpaused(void);
	
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow* window);
	
	bool initialize();
};