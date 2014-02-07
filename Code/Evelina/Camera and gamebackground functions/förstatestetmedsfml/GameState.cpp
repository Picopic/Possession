//GameState.cpp
//Where you play the game. Enter this state from the StartMenuState.

#include "stdafx.h"
#include <string>
#include "GameState.h"

using namespace sf;

GameState::GameState(){

}

GameState::~GameState(){

}

bool GameState::Initialize(){
	m_done = false;
	return false;
}

bool GameState::Enter(){
	std::cout << " " << std::endl;
	std::cout << "Welcome to the GameState" << std::endl;
	std::cout << "This is where you will play the game" <<std::endl;
	std::cout << "Please chose what to do next" << std::endl;
	std::cout << "Press 4 to go back to the StartMenuState" << std::endl;
	std::cout << "Press ESC to exit the game" << std::endl;
	return false;
}

bool GameState::Exit(){
	return false;
}

bool GameState::Update(){

	m_done = false;

	if(Keyboard::isKeyPressed(Keyboard::Num4)){
		m_done=true;
		m_next_state = "StartMenuState";
		return m_done;
	}

	else if(Keyboard::isKeyPressed(Keyboard::Escape)){
		m_done=true;
		return m_done;
	};
}

std::string GameState::Next(){
	return m_next_state;
}

bool GameState::IsType(const std::string& Type){
	return Type == "GameState";
}

bool GameState::Draw(){
	return false;
}
