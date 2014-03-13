//Spritemanager.h

#pragma once

#include <map>
#include <string>

class SpriteManager
{

public:
	SpriteManager();

	bool Initialise(const std::string &directory);
	void Cleanup();

	AnimatedSprite* Load(const std::string &filename, int number_of_frames, int number_of_columns, int width, int height, int startx, int starty);
	void LoadTexture(const std::string &filename);

private:
	bool LoadImage(const std::string &filename);

	std::string directory;
	std::map<std::string, sf::Texture*>spritesheets;
};