//Engine.cpp

#include "Engine.h"
#include <iostream>

Engine::Engine()
{
}

bool Engine::Init()
{
	//Graphics AA
	settings.antialiasingLevel = 4;

	//create the window
	window.create(sf::VideoMode(1280, 720), "Jian", sf::Style::Default, settings);

	draw_manager = new DrawManager;

	return true;
}

void Engine::Run()
{
	while(window.isOpen())
	{
		//Event handling
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


		//drawing portion of engine
		draw_manager->Draw(&window);
	}
}

void Engine::CleanUp()
{
}