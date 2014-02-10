//OptionsState.cpp
//You can choose to enter "Options" from the StartMenuState.
//You can only go back to StartMenuState from here.

#include "stdafx.h"
#include "OptionsState.h"

using namespace sf;

OptionsState::OptionsState(){

}

OptionsState::~OptionsState(){

}

bool OptionsState::Initialize(){
	m_done = false;
	return false;
}

bool OptionsState::Enter(){
	std::cout << " " << std::endl;
	std::cout << "Welcome to the OptionsState" << std::endl;
	std::cout << "Press 6 to go back to the StartMenuState" << std::endl;
	return false;
}

bool OptionsState::Exit(){
	return false;
}

bool OptionsState::Update(){
	m_done=false;

	if (Keyboard::isKeyPressed(Keyboard::Num6)){
	m_done=true;
	m_next_state = "StartMenuState";
	return m_done;
	};
}

std::string OptionsState::Next(){
	return m_next_state;
}

bool OptionsState::IsType(const std::string& Type){
	return Type == "OptionsState";
}

bool OptionsState::Draw(){
	return false;
}
