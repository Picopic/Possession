//SMop2.cpp

#include "stdafx.h"
#include "SMop2.h"


SMop2::SMop2(void){

}


SMop2::~SMop2(void){

}

sf::Vector2f SMop2::getPosition(){
	return position;
}

void SMop2::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMop2::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMop2::initialize(){
	texture.loadFromFile("../data/f/SMtextop2.png");
	sprite.setTexture(texture);

	return true;
}