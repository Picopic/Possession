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
	chosenhowtoplay = false;
	chosenoptions = false;
	chosenquit = false;
}

StartMenuState::~StartMenuState(){

}

bool StartMenuState::Initialize(){

	sprite_manager=new SpriteManager; //lägg till directory

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

	smoptions.setPosition(sf::Vector2f(0,0));
	smoptions.initialize(sprite_manager);

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

	//För att molnen ska spawna och despawna på rätt positioner:
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

	//För att bakre dimma ska spawna och despawna på rätt positioner:
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

	//För att främre dimma ska spawna och despawna på rätt positioner:
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


	if(Keyboard::isKeyPressed(Keyboard::Num2)) {
		m_next_state = "OptionsState";
		m_done=true;

	}

	//Go up in list of menu options
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !options_changed)
	{
		if(!chosenhowtoplay && !chosenoptions){
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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !options_changed)
	{
		if(!chosenhowtoplay && !chosenoptions){
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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !options_changed)
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
			/*		case OPTIONS:
			m_next_state = "OptionsState";
			m_done=true;
			break; */
		case QUIT:
			m_window->close();
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


	/* ************ PLAY */
	if (current_option == PLAY){
		smop1.draw(m_window);
	}

	/* ************ HOW TO PLAY */
	else if (current_option == HOWTOPLAY){
		// Säger att man går in i How to play om den är markerad:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !chosenhowtoplay && !previousisdown && !chosenoptions && !chosenquit){
			chosenhowtoplay = true;
			previousisdown = true;
		}
		// Säger att man går ur How to play om man är inne i den och trycker space:
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && chosenhowtoplay && !previousisdown && !chosenoptions && !chosenquit){
			chosenhowtoplay = false;
			previousisdown = true;
		}
		// Säger att den ska drawa en viss sprite när man är i How to play:
		if(chosenhowtoplay) smhowtoplay.draw(m_window);
		// Säger att den annars ska drawa den markerade How to play-knappen i Startmenyn
		else smop2.draw(m_window);
	}

	/* ************ OPTIONS */
	else if (current_option == OPTIONS){
		// Säger att den går in i Options om den är markerad och man trycker Space:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !chosenhowtoplay && !previousisdown && !chosenoptions && !chosenquit){
			chosenoptions = true;
			previousisdown = true;
		}
		// Säger att man går ur Options om man är inne i den och trycker Space:
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !chosenhowtoplay && !previousisdown && chosenoptions && !chosenquit){
			chosenoptions = false;
			previousisdown = true;
		}
		// Säger att den ska drawa vissa sprites om man har valt Options:
		// Kommer bli en massa ifsatser och styrning med W A S D för att bestämma ljudnivå samt vilket alternativ man markerar 
		if(chosenoptions) smoptions.draw(m_window);

		// Säger att den annars ska drawa den markerade Options-knappen i Startmenyn
		else smop3.draw(m_window);
	}

	/* ************ QUIT GAME */
	else if (current_option == QUIT){
		//smop4.draw(m_window);
		// Säger att den ska sätta Quit till true om den är markerad:
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !chosenhowtoplay && !previousisdown && !chosenoptions){
			chosenoptions = true;
			previousisdown = true;
		}
		// Säger att om man väljer Quit så stängs allt ner:
		//if(chosenquit) så kommer allt stängas ner 

		//Säger att den annars ska drawa den markerade Quit-knappen i Startmenyn
		else smop4.draw(m_window);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) previousisdown = false;

	m_window->display();
	return false;

}

void StartMenuState::UpdateDeltatime(){
	sf::Time temp_time;
	temp_time = game_clock.getElapsedTime();
	deltatime = (temp_time.asSeconds() - previous_time.asSeconds());
	previous_time = temp_time;
}