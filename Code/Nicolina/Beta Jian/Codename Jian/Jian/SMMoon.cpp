//SMMoon.cpp
#include "stdafx.h"
#include "SMMoon.h"


SMMoon::SMMoon(void){

}


SMMoon::~SMMoon(void){

}

sf::Vector2f SMMoon::getPosition(){
	return position;
}

void SMMoon::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMMoon::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMMoon::initialize(){
	texture.loadFromFile("../data/f/SMMoon.png");
	sprite.setTexture(texture);

	return true;
}