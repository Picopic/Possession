//FireEnemy.cpp

#include "stdafx.h"
#include "FireEnemy.h"
#include "Player.h"
//f�r randomfunktionen:
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include <vector>


FireEnemy::FireEnemy(void){
	velocity = sf::Vector2f (0, 0);
}


FireEnemy::~FireEnemy(void){

}

sf::Vector2f FireEnemy::getPosition(){
	return position;
}

void FireEnemy::setPosition(sf::Vector2f pos){
	position = pos;
}

sf::Vector2f FireEnemy::getVelocity(){
	return velocity;
}

void FireEnemy::setVelocity(sf::Vector2f veloc){
	velocity = veloc;
}


void FireEnemy::draw(sf::RenderWindow* window){
	sprite.setPosition(position);
	//sprite.setVelocity(velocity);
	window->draw(sprite);

}
	
bool FireEnemy::initialize(){
	texture.loadFromFile("../bin/P.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
	sprite.setScale(0.40, 0.40);

	//m_random = (rand()%(MAXV�RDET-(MINIMUMV�RDE)+1))+(MINIMUMV�RDE);
	m_random = (rand()%(350-(150)+1))+(150);
	

	return true;
}

void FireEnemy::moveX(float x){
	position.x += x;
}

void FireEnemy::moveY(float y){
	position.y += y;
}

void FireEnemy::Update(Player* player){


		//ENEMYS R�RELSEM�NSTER:
		//F�r att fireenemy ska spawna utanf�r rutan men g� till v�nster:
		setVelocity(sf::Vector2f(-0.3, 0));
		

		//Den ska stanna p� ett visst avst�nd i X-led:
		if (getPosition().x < player->getPosition().x + m_random) {
			sf::Vector2f vect = getPosition();
			vect.x = player->getPosition().x + m_random;
			setVelocity(sf::Vector2f(0, 0));

			//Nu ska fienden stanna om spelaren backar i X-led:
			if (getPosition().x < player->getPosition().x + 450) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(+0.2, 0));
			}
			//Nu ska fienden f�lja efter ner�t i Y-led
			if (getPosition().y + 250 < player->getPosition().y) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(0, +0.2));
			}
			//Nu ska fienden f�lja efter upp�t i Y-led:
			else if (getPosition().y - 250 > player->getPosition().y) {
				sf::Vector2f vect = getPosition();
				setVelocity(sf::Vector2f(0, -0.2));
			}
		}
			
			

		//collission i horisontlinjen:
		/*else if (getPosition().y <= (320/2) - 210){
			sf::Vector2f vect = getPosition();			
			vect.y = (320/2) - 210;
			}
		//collission i nedre kant:
		else if (getPosition().y >= (640)){
			sf::Vector2f vect = getPosition();			
			vect.y = (640);
		}*/



		//N�r den ska skjuta:
		//Nu ska fienden skjuta inom visst Y-led:
		if (getPosition().y <= player->getPosition().y + 100) {
				//SHOOT;
			}
		//Nu ska fienden f�lja efter upp�t i Y-led:
		else if (getPosition().y >= player->getPosition().y + 100) {
			//SHOOT;
		}

		sf::Vector2f movement = sf::Vector2f(getPosition()+getVelocity());
		setPosition(movement);

}