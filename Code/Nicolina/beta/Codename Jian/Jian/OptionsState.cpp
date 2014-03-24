//OptionsState.cpp
//You can choose to enter "Options" from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "OptionsState.h"

using namespace sf;

OptionsState::OptionsState(sf::RenderWindow* OptionWindow){
	m_window = OptionWindow;
}

OptionsState::~OptionsState(){

}

bool OptionsState::Initialize(){
	m_done = false;
	return false;
}

bool OptionsState::Enter(){
	std::cout << "Welcome to the OptionsState" << std::endl;
	std::cout << "Press 4 to go back to StartMenuState" <<std::endl;
	return false;
}

bool OptionsState::Exit(){
	return false;
}

bool OptionsState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Num4)) {
		m_next_state = "StartMenuState";
		m_done=true;
		
	};
	return m_done;
}

std::string OptionsState::Next(){
	return m_next_state;
}

bool OptionsState::IsType(const std::string& Type){
	return Type == "OptionsState";
}

bool OptionsState::Draw(){
	m_window->clear(Color(0x99, 0xff, 0x55, 0xff));
	m_window->display();
	return false;
}
