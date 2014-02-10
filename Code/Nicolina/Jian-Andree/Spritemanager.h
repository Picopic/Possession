//Spritemanager.h

#pragma once

#include <map>
#include <string>


class DrawManager;


class SpriteManager
{
public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

	bool Initialise(const std::string &directory);
	void Cleanup();

	void Load(const std::string &filename, int x, int y, int width, int height, int posx, int posy);

private:
	DrawManager *draw_manager;
	std::string directory;
	std::map<std::string, sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
};