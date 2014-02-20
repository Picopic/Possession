//SpriteManager.cpp

#include "stdafx.h"
#include "AnimatedSprite.h"
#include "SpriteManager.h"

SpriteManager::SpriteManager()
{

}

bool SpriteManager::Initialise(const std::string &img_directory)
{
	directory = img_directory;

	return true;
}

void SpriteManager::Cleanup()
{
	std::map<std::string, sf::Texture*>::iterator it = spritesheets.begin();
	while(it != spritesheets.end())
	{
		delete it->second;
		it->second = nullptr;
		++it;
	}

	spritesheets.clear();
}

AnimatedSprite* SpriteManager::Load(const std::string &filename, int number_of_frames, int number_of_columns, int width, int height, int startx, int starty)
{
	std::map<std::string, sf::Texture*>::iterator it = spritesheets.find(filename);
	if(it == spritesheets.end())
	{
		//Om det inte går att ladda in spritesheeten
		if(!LoadImage(filename))
		{
			return nullptr;
		}

		it = spritesheets.find(filename);
	}
	AnimatedSprite* anim_sprite = new AnimatedSprite(it->second, width, height, startx, starty);
	int row = 0;
	int column = 0;
	for(int i = 1; i <= number_of_frames; i++)
	{
		AnimatedSprite::Frame frame;

		frame.duration = 0.1f;
		frame.x = startx + (column * width);
		frame.y = starty + (row * height);
		frame.w = width;
		frame.h = height;
		anim_sprite->AddFrame(frame);
		
		column ++;

		if(i%number_of_columns == 0)
		{
			column = 0;
			row++;
		}
	}
	return anim_sprite;
}

/*
 * Laddar in ett spritesheet
 * returna false om det inte gick
*/
bool SpriteManager::LoadImage(const std::string &filename)
{
	std::string path = directory + filename;
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	if(texture == nullptr)
	{
		return false;
	}

	spritesheets.insert(std::pair<std::string, sf::Texture*>(filename, texture));
	return true;
}