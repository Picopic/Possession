//SMslider.h

#pragma once

#include "stdafx.h"

class InputManager;
class SpriteManager;

class SMslider 
{
public:
	SMslider(std::string type, sf::Vector2f position, int level);
	~SMslider();
	void Update(InputManager* p_input);
	float GetLevel();

	sf::Sprite* GetSliderSprite();
	sf::Sprite* GetSliderSprite2();

	bool GetType();
	std::string GetSliderType();

private:
	float m_slider_length;

	sf::Texture texture;
	sf::Texture texture2;

	sf::Sprite m_slider;
	sf::Sprite sliderbase;


	sf::Vector2f m_sliderposition;

	float m_level;
	bool m_grabbed;

	std::string m_type;
};