//Gradienthimmel.cpp

#include "stdafx.h"
#include "Gradienthimmel.h"


Gradienthimmel::Gradienthimmel(void){

}


Gradienthimmel::~Gradienthimmel(void){

}

sf::Vector2f Gradienthimmel::getPosition(){
	return position;
}

void Gradienthimmel::setPosition(sf::Vector2f pos){
	position = pos;
}

void Gradienthimmel::draw(sf::RenderWindow* window){
	sprite.setPosition(position);

	window->draw(sprite);

}
	
bool Gradienthimmel::initialize(){
	texture.loadFromFile("../data/f/Gradient himmel.png");
	sprite.setTexture(texture);

	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);

	return true;
}

void Gradienthimmel::moveX(float x){
	position.x += x;
}