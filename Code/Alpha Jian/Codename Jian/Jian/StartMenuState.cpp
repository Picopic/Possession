//StartMenuState.cpp
//The StartMenu
//From the StartMenu you can enter three other states: "GameState"(Play Game), "HowToPlayState"(How to play) and "OptionsState"(Options).
//You will also be able to quit the game(Quit game), but that is not a state.

//När vi lägger ihop StateManagers och EntityManagers så kan vi lägga RenderWindow i GameObjectManager istället för en i varje State.

#include "stdafx.h"
#include "StartMenuState.h"

using namespace sf;

StartMenuState::StartMenuState(sf::RenderWindow* StartMenuWindow){
	m_window = StartMenuWindow;
}

StartMenuState::~StartMenuState(){

}

bool StartMenuState::Initialize(){

	smclouds.setPosition(sf::Vector2f(0, 0));
	smclouds.initialize();

	smfogb.setPosition(sf::Vector2f(0, 0));
	smfogb.initialize();

	smfogf.setPosition(sf::Vector2f(0, 0));
	smfogf.initialize();

	smhimmel.setPosition(sf::Vector2f(0, 0));
	smhimmel.initialize();

	smmoon.setPosition(sf::Vector2f(0, 0));
	smmoon.initialize();

	smmountainsb.setPosition(sf::Vector2f(0, 0));
	smmountainsb.initialize();

	smmountainsf.setPosition(sf::Vector2f(0, 0));
	smmountainsf.initialize();

	smpagoda.setPosition(sf::Vector2f(0, 0));
	smpagoda.initialize();

	m_done = false;
	current_option = PLAY;
	options_changed = false;
	options_changed_delay = 0.001f;

	
	previous_time = game_clock.restart();
	deltatime = 0.01f;

	return false;
}

bool StartMenuState::Enter(){
	std::cout << "Welcome to the StartMenuState" << std::endl;
	std::cout << "Please select which state you want to enter" <<std::endl;
	std::cout << "Press 1 to go to the Gamestate" <<std::endl;
	std::cout << "Press 2 to go to the Optionsstate" <<std::endl;
	std::cout << "Press 3 to go to the HowToPlayState" <<std::endl;
	
	return false;

}

bool StartMenuState::Exit(){
	return false;
}

bool StartMenuState::Update()
{
	m_done = false;
	UpdateDeltatime();

	if(Keyboard::isKeyPressed(Keyboard::Num1)) {
		m_next_state = "GameState";
		m_done=true;
		
	}
	else if(Keyboard::isKeyPressed(Keyboard::Num2)) {
		m_next_state = "OptionsState";
		m_done=true;
		
	}
	else if(Keyboard::isKeyPressed(Keyboard::Num3)) {
		m_next_state = "HowToPlayState";
		m_done=true;
		
	}
	//Go up in list of menu options
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !options_changed)
	{
		switch(current_option)
		{
		case PLAY:
			current_option = QUIT;
			options_changed = true;
		break;
		case HOWTOPLAY:
			current_option = PLAY;
			options_changed = true;
		break;
		case OPTIONS:
			current_option = HOWTOPLAY;
			options_changed = true;
		break;
		case QUIT:
			current_option = OPTIONS;
			options_changed = true;
		break;
		}
		std::cout << current_option << std::endl;
	}

	//Go down in list of menu options
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !options_changed)
	{
		switch(current_option)
		{
		case PLAY:
			current_option = HOWTOPLAY;
			options_changed = true;
		break;
		case HOWTOPLAY:
			current_option = OPTIONS;
			options_changed = true;
		break;
		case OPTIONS:
			current_option = QUIT;
			options_changed = true;
		break;
		case QUIT:
			current_option = PLAY;
			options_changed = true;
		break;
		}
		std::cout << current_option << std::endl;
	}

	//Choose in list of menu options
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !options_changed)
	{
		switch(current_option)
		{
		case PLAY:
			m_next_state = "GameState";
			m_done=true;
		break;
		case HOWTOPLAY:
			m_next_state = "HowToPlayState";
			m_done=true;
		break;
		case OPTIONS:
			m_next_state = "OptionsState";
			m_done=true;
		break;
		case QUIT:
		
		break;
		}
	}


	if(options_changed)
	{
		options_changed_delay += deltatime;
		if(options_changed_delay > 0.5f)
		{
			options_changed = false;
			options_changed_delay = 0.0f;
		}


	}


	return m_done;
}

std::string StartMenuState::Next(){
	return m_next_state;
}

bool StartMenuState::IsType(const std::string& Type){
	return Type == "StartMenuState";
}

bool StartMenuState::Draw(){
	m_window->clear(Color(0x99, 0x20, 0x55, 0xff));
		
		smhimmel.draw(m_window);
		smmoon.draw(m_window);
		smclouds.draw(m_window);
		smmountainsb.draw(m_window);
		smfogb.draw(m_window);
		smmountainsf.draw(m_window);
		smfogf.draw(m_window);
		smpagoda.draw(m_window);

	m_window->display();
	return false;

}

void StartMenuState::UpdateDeltatime(){
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}