//Spritemanager.cpp

#include "stdafx.h"

#include "Spritemanager.h"

SpriteManager::SpriteManager(DrawManager *_draw_manager)
{
	draw_manager = _draw_manager;
}

SpriteManager::~SpriteManager()
{

}

bool SpriteManager::Initialise(const std::string &_directory)
{
	directory = _directory;

	return true;
}

void SpriteManager::Cleanup()
{
	//delete the draw manager pointer
	if(draw_manager != nullptr)
	{
		delete draw_manager;
		draw_manager = nullptr;
	}

	//clear the dynamic arrays
	std::map<std::string, Texture>::iterator it = textures.begin();
	while(it != textures.end()) {
		it->second.~Texture();
		++it;
	};
	textures.clear();

	sprites.clear();
}

void SpriteManager::Load(const std::string &filename, int _x, int _y, int _width, int _height, int posx, int posy)
{
	//Do the texture already exist?
	std::map<std::string, Texture>::iterator it = textures.find(filename);

	//if we reach the end but still have not found the texture we create a new and store it
	if(it == textures.end())
	{
		std::string path = directory + filename;

		textures[filename] = Texture();
		it = textures.find(filename);
		it->second.loadFromFile(path, IntRect(_x, _y, _width, _height));
		it->second.setSmooth(true);

		//Create a new sprite with the texture
		sprites.push_back(Sprite());
		sprites[sprites.size() - 1].setTexture(it->second);
		sprites[sprites.size() - 1].setPosition(posx, posy);
	}
	else
	{
		//Create a new sprite with the texture
		sprites.push_back(Sprite());
		sprites[sprites.size() - 1].setTexture(it->second);
		sprites[sprites.size() - 1].setPosition(posx, posy);
	}
}