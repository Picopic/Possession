//SMslider.cpp

#include "stdafx.h"
#include "SMslider.h"


SMslider::SMslider(std::string type, sf::Vector2f p_position, int level)
{

	texture2.loadFromFile("../data/f/SMoptionsejvald.png");
	texture.loadFromFile("../data/f/SMoptionsscale.png");
	texture3.loadFromFile("../data/f/SMoptionsejoff.png");
	

	m_slider.setTexture(texture2);
	m_slider.setOrigin(m_slider.getLocalBounds().width/2, m_slider.getLocalBounds().height/2);
	m_slider.setPosition(p_position);

	sliderbase.setTexture(texture);
	sliderbase.setOrigin(147, sliderbase.getLocalBounds().height/2);
	sliderbase.setPosition(p_position.x-180, p_position.y);

	onoff.setTexture(texture3);
	onoff.setOrigin(onoff.getLocalBounds().width/2, onoff.getLocalBounds().height/2);
	onoff.setPosition(p_position);
	
	sliderbase.setScale(8*1.205,1);

	m_type = type;
}


SMslider::~SMslider()
{

}

void SMslider::Update(InputManager* p_input)
{


};

float SMslider::GetLevel(){
	return m_level;
};

bool SMslider::GetType(){
	return true;
};

std::string SMslider::GetSliderType(){
	return m_type;
};

sf::Sprite* SMslider::GetSliderSprite(){
	return &m_slider;
};

sf::Sprite* SMslider::GetSliderSprite2(){
	return &sliderbase;
};

sf::Sprite* SMslider::GetonoffSprite(){
	return &onoff;
};