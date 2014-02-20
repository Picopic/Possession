#include "stdafx.h"
#include "Player.h"


Player::Player(void){

}


Player::~Player(void){

}

sf::Vector2f Player::getPosition(){
	return position;
}

void Player::setPosition(sf::Vector2f pos){
	position = pos;
}

void Player::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	window->draw(sprite);

}
	
bool Player::initialize(){
	texture.loadFromFile("../bin/PP.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	sprite.setScale(0.40, 0.40);
	//sprite.setColor(sf::Color( , , , ,0x99));

	sprite.setPosition(position);

	return true;
}

void Player::moveX(float x){
	position.x += x;
}

void Player::moveY(float y){
	position.y += y;
}