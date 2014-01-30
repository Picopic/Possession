//Engine.cpp
#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	window_width = 1280;
	window_height = 720;
	window_anti_aliasing = 4;
}

Engine::~Engine()
{

}

bool Engine::Init()
{
	window_settings.antialiasingLevel = window_anti_aliasing;
	window.create(sf::VideoMode(window_width, window_height), "Jian", sf::Style::Default, window_settings);

	draw_manager = new DrawManager;

	entity_manager = new EntityManager;

	return true;
}

void Engine::Run()
{
	entity_manager->AttachEntity(WATERFOE, Vector2(50.0f, 300.0f), 50, 20);
	entity_manager->AttachEntity(FIREFOE, Vector2(250.0f, 300.0f), 40, 20);

	//gameloop
	while(window.isOpen())
	{
		//event handling
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		//game logic

		//drawing portion of game loop
		draw_manager->Draw(&window, entity_manager);
	}
}

void Engine::Cleanup()
{
	if(draw_manager != nullptr)
	{
		delete draw_manager;
		draw_manager = nullptr;
	}
}