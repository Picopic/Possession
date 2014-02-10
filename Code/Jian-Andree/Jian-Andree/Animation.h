//Animation.h

#pragma once
#include "Spritemanager.h"
#include "Enums.h"


class Animation
{
public:
	Animation();
	
	void LoadAnimation(int number_of_frames, int startx, int starty, int frame_width, int frame_height, int spritesheet_columns, std::string file_name);

	sf::Sprite GetCurrentFrame();
	void UpdateCurrentFrame();

private:
	std::vector<sf::Sprite*>animation_frames;
	int index;
};