//main.cpp

#include "StateManager.h"
#include "State.h"
#include "StartMenuState.h"
#include "OptionsState.h"
#include "GameState.h"
#include "HowToPlayState.h"

int main()
{
	StateManager st_mgr;
	st_mgr.Attach(new GameState);
	st_mgr.Attach(new StartMenuState);
	st_mgr.Attach(new OptionsState);
	st_mgr.Attach(new HowToPlayState);

	st_mgr.Initialize();

	st_mgr.SetState("StartMenuState");
	while (true){
		st_mgr.Update();
	}
	
}