//Engine.h

#pragma once

#include "DrawManager.h"

using namespace sf;

class Engine
{
public:
	Engine();
	~Engine();
	
	bool Init();
	void Run();
	void Cleanup();

	DrawManager *draw_manager;

private:
	RenderWindow window;
	ContextSettings window_settings;
	int window_width;
	int window_height;
	int window_anti_aliasing;
};