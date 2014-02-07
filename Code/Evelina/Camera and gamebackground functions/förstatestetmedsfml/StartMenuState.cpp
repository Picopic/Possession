//StartMenuState.cpp
//The StartMenu
//From the StartMenu you can enter three other states: "GameState"(Play Game), "HowToPlayState"(How to play) and "OptionsState"(Options).
//You will also be able to quit the game(Quit game), but that is not a state.

#include "stdafx.h"
#include <string>

#include "StartMenuState.h"

using namespace sf;

StartMenuState::StartMenuState(){

}

StartMenuState::~StartMenuState(){

}

bool StartMenuState::Initialize(){
	m_done = false;
	return false;
}

bool StartMenuState::Enter(){
	std::cout << " " << std::endl;
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

bool StartMenuState::Update(){

	m_done = false;

	if (Keyboard::isKeyPressed(Keyboard::Num1)){
		m_done=true;
		m_next_state = "GameState";
		return m_done;}

	else if (Keyboard::isKeyPressed(Keyboard::Num2)){
		m_done=true;
		m_next_state = "OptionsState";
		return m_done;}

	else if (Keyboard::isKeyPressed(Keyboard::Num3)){
		m_done=true;
		m_next_state = "HowToPlayState";
		return m_done;}
}

std::string StartMenuState::Next(){
	return m_next_state;
}

bool StartMenuState::IsType(const std::string& Type){
	return Type == "StartMenuState";
}

bool StartMenuState::Draw(){
	return false;
}
