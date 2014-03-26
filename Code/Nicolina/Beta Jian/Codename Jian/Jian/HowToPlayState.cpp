//HowToPlayState.cpp
//Enter this state from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "HowToPlayState.h"

using namespace sf;

HowToPlayState::HowToPlayState(sf::RenderWindow* HowToPlayWindow){
	m_window = HowToPlayWindow;
}

HowToPlayState::~HowToPlayState(){

}

bool HowToPlayState::Initialize(){
	m_done = false;
	return false;
}

bool HowToPlayState::Enter(){
	
	std::cout << "Welcome to the HowToPlayState" << std::endl;
	std::cout << "Press 4 to go back to StartMenuState" <<std::endl;
	return false;
}

bool HowToPlayState::Exit(){
	return false;
}

bool HowToPlayState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Num4)) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};
	return m_done;
}

std::string HowToPlayState::Next(){
	return m_next_state;
}

bool HowToPlayState::IsType(const std::string& Type){
	return Type == "HowToPlayState";
}

bool HowToPlayState::Draw(){
	m_window->clear(Color(0x99, 0x55, 0x99, 0xff));
	m_window->display();
	return false;
}