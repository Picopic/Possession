//StartMenuState.cpp
//The StartMenu
//From the StartMenu you can enter three other states: "GameState"(Play Game), "HowToPlayState"(How to play) and "OptionsState"(Options).
//You will also be able to quit the game(Quit game), but that is not a state.

//N�r vi l�gger ihop StateManagers och EntityManagers s� kan vi l�gga RenderWindow i GameObjectManager ist�llet f�r en i varje State.

#include "stdafx.h"
#include "StartMenuState.h"

using namespace sf;

StartMenuState::StartMenuState(sf::RenderWindow* StartMenuWindow){
	m_window = StartMenuWindow;
	chosenhowtoplay = false;
}

StartMenuState::~StartMenuState(){

}

bool StartMenuState::Initialize(){

	smclouds.setPosition(sf::Vector2f(0, 0));
	smclouds.initialize();
	smclouds2.setPosition(sf::Vector2f(3840, 0));
	smclouds2.initialize();

	smfogb.setPosition(sf::Vector2f(0, 0));
	smfogb.initialize();
	smfogb2.setPosition(sf::Vector2f(3840, 0));
	smfogb2.initialize();

	smfogf.setPosition(sf::Vector2f(0, 0));
	smfogf.initialize();
	smfogf2.setPosition(sf::Vector2f(3840, 0));
	smfogf2.initialize();

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

	smop1.setPosition(sf::Vector2f(0, 0));
	smop1.initialize();

	smop2.setPosition(sf::Vector2f(0, 0));
	smop2.initialize();

	smop3.setPosition(sf::Vector2f(0, 0));
	smop3.initialize();

	smop4.setPosition(sf::Vector2f(0, 0));
	smop4.initialize();

	smhowtoplay.setPosition(sf::Vector2f(0, 0));
	smhowtoplay.initialize();

	m_done = false;
	current_option = PLAY;
	options_changed = false;
	options_changed_delay = 0.001f;


	previous_time = game_clock.restart();
	deltatime = 0.01f;

	return false;
}

bool StartMenuState::Enter(){
	m_window->setView(m_window->getDefaultView());

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

	smclouds.moveX(-0.2);
	smclouds2.moveX(-0.2);

	smfogb.moveX(-0.25);
	smfogb2.moveX(-0.25);

	smfogf.moveX(-0.45);
	smfogf2.moveX(-0.45);

	//F�r att molnen ska spawna och despawna p� r�tt positioner:
	if(smclouds.getPosition().x <= -3840){
		sf::Vector2f vect = smclouds.getPosition();
		vect.x = 3840;
		smclouds.setPosition(vect);
	}
	if(smclouds2.getPosition().x <= -3840){
		sf::Vector2f vect = smclouds2.getPosition();
		vect.x = 3840;
		smclouds2.setPosition(vect);
	}

	//F�r att bakre dimma ska spawna och despawna p� r�tt positioner:
	if(smfogb.getPosition().x <= -3840){
		sf::Vector2f vect = smfogb.getPosition();
		vect.x = 3840;
		smfogb.setPosition(vect);
	}
	if(smfogb2.getPosition().x <= -3840){
		sf::Vector2f vect = smfogb2.getPosition();
		vect.x = 3840;
		smfogb2.setPosition(vect);
	}

	//F�r att fr�mre dimma ska spawna och despawna p� r�tt positioner:
	if(smfogf.getPosition().x <= -3840){
		sf::Vector2f vect = smfogf.getPosition();
		vect.x = 3840;
		smfogf.setPosition(vect);
	}
	if(smfogf2.getPosition().x <= -3840){
		sf::Vector2f vect = smfogf2.getPosition();
		vect.x = 3840;
		smfogf2.setPosition(vect);
	}


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
		if(!chosenhowtoplay){
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
	}
	//Go down in list of menu options
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !options_changed)
	{
		if(!chosenhowtoplay){
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
			/*		case HOWTOPLAY:

			m_next_state = "HowToPlayState";
			m_done=true;
			break;*/
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
	smclouds2.draw(m_window);

	smmountainsb.draw(m_window);

	smfogb.draw(m_window);
	smfogb2.draw(m_window);

	smmountainsf.draw(m_window);

	smfogf.draw(m_window);
	smfogf2.draw(m_window);

	smpagoda.draw(m_window);

	if (current_option == PLAY){
		smop1.draw(m_window);
	}
	else if (current_option == HOWTOPLAY){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !chosenhowtoplay && !previousisdown){
			chosenhowtoplay = true;
			previousisdown = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && chosenhowtoplay && !previousisdown){
			chosenhowtoplay = false;
			previousisdown = true;
		}
		if(chosenhowtoplay) smhowtoplay.draw(m_window);
		else smop2.draw(m_window);
	}
	else if (current_option == OPTIONS){
		smop3.draw(m_window);
	}
	else if (current_option == QUIT){
		smop4.draw(m_window);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) previousisdown = false;

	m_window->display();
	return false;

}

void StartMenuState::UpdateDeltatime(){
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}