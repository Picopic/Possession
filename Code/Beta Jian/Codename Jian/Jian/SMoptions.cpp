//SMoptions.cpp

#include "stdafx.h"
#include "SMoptions.h"


SMoptions::SMoptions(void){

}


SMoptions::~SMoptions(void){

}

sf::Vector2f SMoptions::getPosition(){
	return position;
}

void SMoptions::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMoptions::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMoptions::initialize(){
	texture.loadFromFile("../data/Spritesheets2/SMoptionsstatic.png");
	sprite.setTexture(texture);

	return true;
}