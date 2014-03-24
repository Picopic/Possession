//SMMountainsF.cpp
#include "stdafx.h"
#include "SMMountainsF.h"


SMMountainsF::SMMountainsF(void){

}


SMMountainsF::~SMMountainsF(void){

}

sf::Vector2f SMMountainsF::getPosition(){
	return position;
}

void SMMountainsF::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMMountainsF::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMMountainsF::initialize(){
	texture.loadFromFile("../data/f/SMMountainsF.png");
	sprite.setTexture(texture);

	return true;
}