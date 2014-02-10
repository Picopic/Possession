//GameState.cpp
//Where you play the game. Enter this state from the StartMenuState.

#include "stdafx.h"
#include "GameState.h"

GameState::GameState(){

}

GameState::~GameState(){

}

bool GameState::Initialize(){
	m_done = false;
	return false;
}

bool GameState::Enter(){
	return false;
}

bool GameState::Exit(){
	return false;
}

bool GameState::Update(){
	std::cout << "GameState!!! WOOOH PARTEEEHHH!!" << std::endl;
	m_done = true;
	m_next_state = "OptionsState";
	return m_done;
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
