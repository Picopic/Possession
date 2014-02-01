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

	previous_time = game_clock.restart();

	deltatime = 0.01f;
	

	return true;
}

void Engine::Run()
{
	entity_manager->Init(&keyboard);
	entity_manager->AttachEntity(WATERFOE, Vector2(50.0f, 300.0f), 50, 20, WATER);
	entity_manager->AttachEntity(FIREFOE, Vector2(250.0f, 300.0f), 40, 20, FIRE);

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

		//deltatime
		UpdateDeltatime();

		//game logic

		//horizontal movement player
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			keyboard.setA(true);
			keyboard.setD(false);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			keyboard.setD(true);
			keyboard.setA(false);
		}
		else
		{
			keyboard.setA(false);
			keyboard.setD(false);
		}

		//vertical movement player
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			keyboard.setW(true);
			keyboard.setS(false);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			keyboard.setS(true);
			keyboard.setW(false);
		}
		else
		{
			keyboard.setW(false);
			keyboard.setS(false);
		}

		entity_manager->Update(deltatime);

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

void Engine::UpdateDeltatime()
{
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}