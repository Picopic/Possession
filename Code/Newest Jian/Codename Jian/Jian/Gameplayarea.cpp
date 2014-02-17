#include "stdafx.h"
#include "Gameplayarea.h"


Gameplayarea::Gameplayarea(void){

}


Gameplayarea::~Gameplayarea(void){

}

sf::Vector2f Gameplayarea::getPosition(){
	return position;
}

void Gameplayarea::setPosition(sf::Vector2f pos){
	position = pos;
}

void Gameplayarea::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);
}
	
bool Gameplayarea::initialize(){
	texture.loadFromFile("../data/background/Placeholder Play Area Big.png");
	sprite.setTexture(texture);

	return true;
}