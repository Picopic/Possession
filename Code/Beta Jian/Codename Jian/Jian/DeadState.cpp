//DeadState.cpp
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "DeadState.h"

using namespace sf;

DeadState::DeadState(sf::RenderWindow* DeadState){
	
	deadtexture.loadFromFile("../data/f/Dead.png");
	
	deadsprite.setTexture(deadtexture);
	//badwinsprite.setOrigin(m_slider.getLocalBounds().width/2, m_slider.getLocalBounds().height/2);
	deadsprite.setPosition(0,0);

	m_window = DeadState;
	m_clock = nullptr;
}

DeadState::~DeadState(){

}

bool DeadState::Initialize(){
	m_done = false;
	return false;
}

bool DeadState::Enter(){
	
	if (m_clock != nullptr)
	{
		delete m_clock;
	}

	m_clock = new sf::Clock();

	std::cout << "Welcome to the DeadState" << std::endl;
	return false;
}

bool DeadState::Exit(){
	return false;
}

bool DeadState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Return) || m_clock->getElapsedTime().asSeconds() > 3.0f) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};
	return m_done;
}

std::string DeadState::Next(){
	return m_next_state;
}

bool DeadState::IsType(const std::string& Type){
	return Type == "DeadState";
}

bool DeadState::Draw(){

	
	m_window->setView(m_window->getDefaultView());
	
	m_window->clear();

	m_window->draw(deadsprite);

	m_window->display();
	return false;
}
