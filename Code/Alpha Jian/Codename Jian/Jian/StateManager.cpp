//StateManager.cpp
//�r lite annorlunda. Hanterar alla states, s�ger vilken som g�ller atm, vilken ordning de k�rs i o s�nt!

#include "stdafx.h"
#include "StateManager.h"
#include "State.h"



StateManager::StateManager(){
	m_currentstate=nullptr;
}

StateManager::~StateManager(){
	auto it = m_states.begin();
	while (it!=m_states.end()){
	delete(*it);
		it++;
	};
}

void StateManager::SetState(const std::string& type){
	for(unsigned int i=0; i<m_states.size(); i++){
		if(m_states[i]->IsType(type)) {
			m_currentstate = m_states[i];
			m_currentstate->Enter();
			return;
		}
	}
}

void StateManager::ChangeState(){
	std::string next = m_currentstate->Next();

	if (m_currentstate != nullptr) {
		m_currentstate->Exit();
		m_currentstate = nullptr;

						};

	for(unsigned int i=0; i<m_states.size(); i++){
		if(m_states[i]->IsType(next)) {
			m_currentstate = m_states[i];
			m_currentstate->Enter();
			return;
		}
	}
}

void StateManager::Attach(State* state){
	m_states.push_back(state);
}

void StateManager::Update(){
	if(m_currentstate == nullptr) {
		return;
	}

	if(m_currentstate->Update()){
		ChangeState();
	}
}

void StateManager::Draw(){
	if(m_currentstate == nullptr) {
		return;
	}

	m_currentstate->Draw();
}
	//IsRunning �r till f�r att kolla om spelet har startat. S�kerhetskontrolltest typ. Fett bra.
bool StateManager::IsRunning(){
	return m_currentstate != nullptr;
}

bool StateManager::Initialize(){
	for (unsigned int i =0; i < m_states.size(); i++){
		if(!m_states.at(i)->Initialize())
		{
			return false;
		}
	};
	return true;
}

void StateManager::Cleanup(){
/*	for (unsigned int i =0; i < m_states.size(); i++){
		m_states.at(i)->Cleanup();
	};*/
}
