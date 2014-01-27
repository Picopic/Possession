//Drawmanager.h

#include <SFML/Graphics.hpp>

class DrawManager
{
public:
	DrawManager();

	void Draw(sf::RenderWindow *window);

private:
	sf::CircleShape shape;
};