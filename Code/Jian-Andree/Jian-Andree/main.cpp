//main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Engine.h"

int main()
{
	Engine engine;

	if(engine.Init())
	{
		engine.Run();
	}

	engine.CleanUp();
}