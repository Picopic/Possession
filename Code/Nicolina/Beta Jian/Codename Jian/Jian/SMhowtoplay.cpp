//SMhowtoplay.cpp


#include "stdafx.h"
#include "SMhowtoplay.h"


SMhowtoplay::SMhowtoplay(void){

}


SMhowtoplay::~SMhowtoplay(void){

}

sf::Vector2f SMhowtoplay::getPosition(){
	return position;
}

void SMhowtoplay::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMhowtoplay::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMhowtoplay::initialize(){
	texture.loadFromFile("../data/f/SMHowtoplay.png");
	sprite.setTexture(texture);

	return true;
}