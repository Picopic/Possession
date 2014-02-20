//WoodEnemy.cpp

#include "stdafx.h"
#include "WoodEnemy.h"
#include "Player.h"
//för randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>


WoodEnemy::WoodEnemy(void){
	velocity = sf::Vector2f (0, 0);
}


WoodEnemy::~WoodEnemy(void){

}

sf::Vector2f WoodEnemy::getPosition(){
	return position;
}

void WoodEnemy::setPosition(sf::Vector2f pos){
	position = pos;
}

sf::Vector2f WoodEnemy::getVelocity(){
	return velocity;
}

void WoodEnemy::setVelocity(sf::Vector2f veloc){
	velocity = veloc;
}


void WoodEnemy::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	//sprite.setVelocity(velocity);
	window->draw(sprite);

}
	
bool WoodEnemy::initialize(){
	texture.loadFromFile("../bin/T.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height);
	sprite.setScale(0.30, 0.30);

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(500-(50)+1))+(50);

	return true;
}

void WoodEnemy::moveX(float x){
	position.x += x;
}

void WoodEnemy::moveY(float y){
	position.y += y;
}

void WoodEnemy::Update(Player* player){


		//ENEMYS RÖRELSEMÖNSTER:
		//För att waterenemy ska spawna utanför rutan men gå till vänster:
		setVelocity(sf::Vector2f(-0.6, 0));

		//Den ska stanna på ett visst avstånd i X-led:
		if (getPosition().x < player->getPosition().x + m_random) {
			sf::Vector2f vect = getPosition();
			vect.x = player->getPosition().x + m_random;
			setVelocity(sf::Vector2f(0, 0));

			//Nu ska fienden backa om spelaren går för nära den X-led:
			if (getPosition().x < player->getPosition().x + 450) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(+0.4, 0));
			}

			//Nu ska fienden följa efter neråt i Y-led
			if (getPosition().y + 100 < player->getPosition().y) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(0, +0.2));
			}
			//Nu ska fienden följa efter uppåt i Y-led:
			else if (getPosition().y - 100 > player->getPosition().y) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(0, -0.2));
			}
			
		}

		//collission i horisontlinjen:
		if (getPosition().y <= (320/2) - 210){
			sf::Vector2f vect = getPosition();			
			vect.y = (320/2) - 210;
			}
		//collission i nedre kant:
		else if (getPosition().y >= (640)){
			sf::Vector2f vect = getPosition();			
			vect.y = (640);
		}

		//När den ska skjuta:
		//Nu ska fienden skjuta inom visst Y-led:
		if (getPosition().y <= player->getPosition().y + 100) {
			//SHOOT;
			}
		//Nu ska fienden följa efter uppåt i Y-led:
		else if (getPosition().y >= player->getPosition().y + 100) {
			//SHOOT;
		}

		sf::Vector2f movement = sf::Vector2f(getPosition()+getVelocity());
		setPosition(movement);

}