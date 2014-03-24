//SMop4.cpp


#include "stdafx.h"
#include "SMop4.h"


SMop4::SMop4(void){

}


SMop4::~SMop4(void){

}

sf::Vector2f SMop4::getPosition(){
	return position;
}

void SMop4::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMop4::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMop4::initialize(){
	texture.loadFromFile("../data/f/SMtextop4.png");
	sprite.setTexture(texture);

	return true;
}