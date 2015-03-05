//BadWinState.cpp
//You can choose to enter "Options" from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "BadWinState.h"

using namespace sf;

BadWinState::BadWinState(sf::RenderWindow* OptionWindow){
	
	badwintexture.loadFromFile("../data/f/BadWin.png");
	
	badwinsprite.setTexture(badwintexture);
	//badwinsprite.setOrigin(m_slider.getLocalBounds().width/2, m_slider.getLocalBounds().height/2);
	badwinsprite.setPosition(0,0);

	m_window = OptionWindow;
	m_clock = nullptr;
}

BadWinState::~BadWinState(){

}

bool BadWinState::Initialize(){
	m_done = false;
	return false;
}

bool BadWinState::Enter(){
	std::cout << "Welcome to the BadWinState" << std::endl;

	if (m_clock != nullptr)
	{
		delete m_clock;
	}

	m_clock = new sf::Clock();
	return false;
}

bool BadWinState::Exit(){
	return false;
}

bool BadWinState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Return) || m_clock->getElapsedTime().asSeconds() > 3.0f) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};

	std::cout << "Welcome to the GoodWinState" << std::endl;

	if (m_clock != nullptr)
	{
		delete m_clock;
	}

	m_clock = new sf::Clock();
	return m_done;
}

std::string BadWinState::Next(){
	return m_next_state;
}

bool BadWinState::IsType(const std::string& Type){
	return Type == "BadWinState";
}

bool BadWinState::Draw(){
	m_window->setView(m_window->getDefaultView());
	
	m_window->clear();

	m_window->draw(badwinsprite);

	m_window->display();
	return false;
}
