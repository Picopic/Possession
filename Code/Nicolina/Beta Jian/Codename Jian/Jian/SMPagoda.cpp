//SMPagoda.cpp
#include "stdafx.h"
#include "SMPagoda.h"


SMPagoda::SMPagoda(void){

}


SMPagoda::~SMPagoda(void){

}

sf::Vector2f SMPagoda::getPosition(){
	return position;
}

void SMPagoda::setPosition(sf::Vector2f pos){
	position = pos;
}

void SMPagoda::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool SMPagoda::initialize(){
	texture.loadFromFile("../data/f/SMPagoda.png");
	sprite.setTexture(texture);

	return true;
}