//main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Jian", sf::Style::Default, settings);

	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				//pressing escape should shut down the program
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		window.clear();

		window.display();
	}
}