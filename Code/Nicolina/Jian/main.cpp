

#include "stdafx.h"
#include <string>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	enum Direction { Down, Up, Left, Right};

	sf::Vector2i source(1, Down);

	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

	sf::RenderWindow window(sf::VideoMode(1024, 640), "GAME");

	window.setKeyRepeatEnabled(false);
	
	sf::Sprite playerSprite;
	sf::Texture pTexture;
	sf::Clock clock;

	if(!pTexture.loadFromFile("super_cool_sprite.png"))
		std::cout << "Error could not load image" << std::endl;

	playerSprite.setTexture(pTexture);
	playerSprite.setPosition(100, 100);

	while(window.isOpen())
	{
		//Event handling
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Keyboard::Escape:
				window.close();
				break;				
			}
		}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					source.y = Up;
					playerSprite.move(0, -1);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					source.y = Down;
					playerSprite.move(0, 1);
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					source.y = Right;
					playerSprite.move(1, 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					source.y = Left;
					playerSprite.move(-1, 0);
				}


		frameCounter += frameSpeed * clock.restart().asSeconds();
		if(frameCounter >= switchFrame) {
			frameCounter = 0;
			source.x++;
			if(source.x * 32 >= pTexture.getSize().x){
				source.x = 0;
			}
		}

		playerSprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
		window.clear(sf::Color(0x11, 0x22, 0x33, 0xff));
		window.draw(playerSprite);
		window.display();
		window.clear();

	}

	return 0;
}

