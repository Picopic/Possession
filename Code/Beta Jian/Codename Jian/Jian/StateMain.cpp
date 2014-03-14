//main.cpp

#include "stdafx.h"

#include "StateManager.h"
#include "State.h"
#include "StartMenuState.h"
#include "OptionsState.h"
#include "GameState.h"
#include "HowToPlayState.h"
#include "ConfigManager.h"

using namespace sf;

int main()
{
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

	m_window = new sf::RenderWindow(VideoMode(window_width,window_height), "Possession", sf::Style::/*Default*/Fullscreen, window_settings);


	StateManager st_mgr;
	st_mgr.Attach(new GameState(m_window));
	st_mgr.Attach(new StartMenuState(m_window));
	st_mgr.Attach(new OptionsState(m_window));
	st_mgr.Attach(new HowToPlayState(m_window));

	st_mgr.Initialize();

	st_mgr.SetState("StartMenuState");
	while (m_window->isOpen()){
		//Denna pollen är onödig, då det tydligen körs en poll i själva staten också
		//Event event;
		//while(m_window->pollEvent(event)) {
		//	if(event.type == Event::Closed) {
		//		m_window->close();
		//	};
		//	if(Keyboard::isKeyPressed(Keyboard::Escape)) {
		//		m_window->close();
		//	}
		//};
		st_mgr.Update();
		//m_window->clear(Color(0x99, 0x20, 0x55, 0xff));
		st_mgr.Draw();
		//m_window->display();
	}
	return 0;
}
