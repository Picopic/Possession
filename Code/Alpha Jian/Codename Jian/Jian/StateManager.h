//StateManager.h
//Är lite annorlunda. Hanterar alla states, säger vilken som gäller atm, vilken ordning de körs i o sånt!

#pragma once

#include <vector>
#include <string>

class State;

class StateManager{
public:
	StateManager();
	~StateManager();
	void SetState(const std::string &type);
	void ChangeState();
	void Attach(State* state);
	void Update();
	void Draw();
	//IsRunning är till för att kolla om spelet har startat. Säkerhetskontrolltest typ. Fett bra.
	bool IsRunning();
	bool Initialize();

	void Cleanup();

private:
	std::vector<State*> m_states;
	State* m_currentstate;
};