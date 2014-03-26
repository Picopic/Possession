//SMop1.cpp

#include "stdafx.h"
#include "SMop1.h"


SMop1::SMop1(void){

}


SMop1::~SMop1(void){

}

sf::Vector2f SMop1::getPosition(){
	return position;
}

void SMop1::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMop1::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMop1::initialize(){
	texture.loadFromFile("../data/f/SMtextop1.png");
	sprite.setTexture(texture);

	return true;
}