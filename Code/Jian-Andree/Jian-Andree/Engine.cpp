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
	window.create(VideoMode(window_width, window_height), "Jian", Style::Default, window_settings);

	draw_manager = new DrawManager;

	return true;
}

void Engine::Run()
{
	//gameloop
	while(window.isOpen())
	{
		//event handling
		Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if(event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		//game logic

		//drawing portion of game loop
		draw_manager->Draw(&window);
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