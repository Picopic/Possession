//SMMountainsB.cpp
#include "stdafx.h"
#include "SMMountainsB.h"


SMMountainsB::SMMountainsB(void){

}


SMMountainsB::~SMMountainsB(void){

}

sf::Vector2f SMMountainsB::getPosition(){
	return position;
}

void SMMountainsB::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMMountainsB::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMMountainsB::initialize(){
	texture.loadFromFile("../data/f/SMMountainsB.png");
	sprite.setTexture(texture);

	return true;
}