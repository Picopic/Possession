//WaterEnemy.cpp

#include "stdafx.h"
#include "WaterEnemy.h"
#include "Player.h"
//för randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>


WaterEnemy::WaterEnemy(void){
	velocity = sf::Vector2f (0, 0);
}


WaterEnemy::~WaterEnemy(void){

}

sf::Vector2f WaterEnemy::getPosition(){
	return position;
}

void WaterEnemy::setPosition(sf::Vector2f pos){
	position = pos;
}

sf::Vector2f WaterEnemy::getVelocity(){
	return velocity;
}

void WaterEnemy::setVelocity(sf::Vector2f veloc){
	velocity = veloc;
}


void WaterEnemy::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	//sprite.setVelocity(velocity);
	window->draw(sprite);

}
	
bool WaterEnemy::initialize(){
	texture.loadFromFile("../bin/W.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height-(sprite.getLocalBounds().height/10));
	sprite.setScale(0.40, 0.40);

	//m_random = (rand()%(MAXVÄRDET-(MINIMUMVÄRDE)+1))+(MINIMUMVÄRDE);
	m_random = (rand()%(550-(400)+1))+(400);

	return true;
}

void WaterEnemy::moveX(float x){
	position.x += x;
}

void WaterEnemy::moveY(float y){
	position.y += y;
}

void WaterEnemy::Update(Player* player){


		//ENEMYS RÖRELSEMÖNSTER:
		//För att waterenemy ska spawna utanför rutan men gå till vänster:
		setVelocity(sf::Vector2f(-0.1, 0));

		//Den ska stanna på ett visst avstånd i X-led:
		if (getPosition().x < player->getPosition().x + m_random) {
			sf::Vector2f vect = getPosition();
			vect.x = player->getPosition().x + m_random;
			setVelocity(sf::Vector2f(0, 0));

			//Nu ska fienden backa om spelaren går för nära den X-led:
			if (getPosition().x < player->getPosition().x + 450) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(+0.2, 0));
			}

			//Nu ska fienden följa efter neråt i Y-led
			if (getPosition().y + 200 < player->getPosition().y) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(0, +0.2));
			}
			//Nu ska fienden följa efter uppåt i Y-led:
			else if (getPosition().y - 200 > player->getPosition().y) {
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

void WaterEnemy::CheckCollision(WaterEnemy* waterenemy){
	//cirkelcolisiosn
	float deltaY = position.y - waterenemy->getPosition().y;
	float deltaX = position.x - waterenemy->getPosition().x;
	float distance = sqrt(deltaY*deltaY+deltaX*deltaX);
	//float offset = sprite.getLocalBounds().width - distance;

	offsetY=deltaY/distance 

	if (distance < sprite.getLocalBounds().width){
		

	}

}