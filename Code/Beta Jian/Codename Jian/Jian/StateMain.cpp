//main.cpp

#include "stdafx.h"

#include "StateManager.h"
#include "State.h"
#include "StartMenuState.h"
#include "BadWinState.h"
#include "GameState.h"
#include "GoodWinState.h"
#include "DeadState.h"
#include "ConfigManager.h"

#include <ctime>

using namespace sf;

int main()
{
	//Create a new seed for randomisation
	srand(time(NULL));

	sf::RenderWindow* m_window;

	ConfigManager *config_manager = new ConfigManager;
	config_manager->Initialise("../data/Configs/");

	config_manager->ReadFile("Config.txt");

	int window_height;
	int window_width;
	std::string m_sInputString;
	sf::ContextSettings window_settings;

	m_sInputString = config_manager->GetValueFromKey("WindowWidth");
	window_width = std::stoi(m_sInputString);

	m_sInputString = config_manager->GetValueFromKey("WindowHeight");
	window_height = std::stoi(m_sInputString);

	m_sInputString = config_manager->GetValueFromKey("WindowAntiAliasing");
	window_settings.antialiasingLevel = std::stoi(m_sInputString);

	m_window = new sf::RenderWindow(VideoMode(window_width,window_height), "Possession", sf::Style::Fullscreen, window_settings);

	//m_window = new sf::RenderWindow(VideoMode(window_width,window_height), "Possession", sf::Style::Default, window_settings);
	

	StateManager st_mgr;
	st_mgr.Attach(new GameState(m_window));
	st_mgr.Attach(new StartMenuState(m_window));
	st_mgr.Attach(new BadWinState(m_window));
	st_mgr.Attach(new GoodWinState(m_window));
	st_mgr.Attach(new DeadState(m_window));

	st_mgr.Initialize();

	st_mgr.SetState("StartMenuState");
	while (m_window->isOpen()){
		Event event;
		while(m_window->pollEvent(event)) {
			if(event.type == Event::Closed) {
				m_window->close();
			};
			if(Keyboard::isKeyPressed(Keyboard::Escape)) {
				m_window->close();
			}
			if(Keyboard::isKeyPressed(Keyboard::F2))
			{
				if(st_mgr.GetState("GameState")->draw_hitbox)
					st_mgr.GetState("GameState")->draw_hitbox = false;
				else
					st_mgr.GetState("GameState")->draw_hitbox = true;
			}
		};
		st_mgr.Update();
		//m_window->clear(Color(0x99, 0x20, 0x55, 0xff));
		st_mgr.Draw();
		//m_window->display();
	}
	return 0;
}
