//SMHimmel.cpp

#include "stdafx.h"
#include "SMHimmel.h"


SMHimmel::SMHimmel(void){

}


SMHimmel::~SMHimmel(void){

}

sf::Vector2f SMHimmel::getPosition(){
	return position;
}

void SMHimmel::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMHimmel::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMHimmel::initialize(){
	texture.loadFromFile("../data/f/SMHimmel.png");
	sprite.setTexture(texture);

	return true;
}