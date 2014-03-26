//StateManager.h
//�r lite annorlunda. Hanterar alla states, s�ger vilken som g�ller atm, vilken ordning de k�rs i o s�nt!

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
	//IsRunning �r till f�r att kolla om spelet har startat. S�kerhetskontrolltest typ. Fett bra.
	bool IsRunning();
	bool Initialize();

	State* GetState(std::string name);

	void Cleanup();

private:
	std::vector<State*> m_states;
	State* m_currentstate;
};