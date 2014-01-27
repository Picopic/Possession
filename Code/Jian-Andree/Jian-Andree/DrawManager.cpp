//Drawmanager.cpp

#include "DrawManager.h"

DrawManager::DrawManager()
{
	shape.setRadius(50);
	shape.setPosition(200, 200);
}

void DrawManager::Draw(sf::RenderWindow *window)
{
	//clear the screen
	window->clear();

	window->draw(shape);

	window->display();
}