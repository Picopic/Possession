

#include "stdafx.h"
#include <string>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	enum Direction { Down, Left, Right, Up};

	sf::Vector2i source(1, Down);

	sf::RenderWindow window(sf::VideoMode(1024, 640), "GAME");

	window.setKeyRepeatEnabled(false);
	
	sf::Sprite playerSprite;
	sf::Texture pTexture;
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
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Up)
					source.y = Up;
				else if(event.key.code == sf::Keyboard::Down)
					source.y = Down;
				else if(event.key.code == sf::Keyboard::Right)
					source.y = Right;
				else if (event.key.code == sf::Keyboard::Left)
					source.y = Left;
					break;
				
			}
		}
		source.x++;
		if(source.x * 32 >= pTexture.getSize().x)
			source.x = 0;


		playerSprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
		window.clear(sf::Color(0x11, 0x22, 0x33, 0xff));
		window.draw(playerSprite);
		window.display();
		window.clear();

	}

	return 0;
}

