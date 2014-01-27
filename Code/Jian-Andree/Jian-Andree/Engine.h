//Engine.h

#include <SFML/Graphics.hpp>

#include "DrawManager.h"

class Engine
{
	sf::ContextSettings settings;
	sf::RenderWindow window;

	DrawManager *draw_manager;

public:
	Engine();

	bool Init();
	void Run();
	void CleanUp();
};