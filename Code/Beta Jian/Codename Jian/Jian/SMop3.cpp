//SMop3.cpp

#include "stdafx.h"
#include "SMop3.h"


SMop3::SMop3(void){

}


SMop3::~SMop3(void){

}

sf::Vector2f SMop3::getPosition(){
	return position;
}

void SMop3::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMop3::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMop3::initialize(){
	texture.loadFromFile("../data/f/SMtextop2.png");
	sprite.setTexture(texture);

	return true;
}