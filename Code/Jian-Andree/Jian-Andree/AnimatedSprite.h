//AnimatedSprite.h

#pragma once

class AnimatedSprite
{
public:
	struct Frame
	{
		float duration;
		int x,y,w,h;
	};

	AnimatedSprite(sf::Texture* spritesheet, int width, int height, int x, int y);

	sf::Sprite* getSprite();

	void Update(float deltatime);
	void AddFrame(Frame &frame);
	int GetNumberOfFrames();
	float GetFrameDuration();

private:
	sf::Sprite* image;
	sf::Texture* spritesheet;
	float x, y;
	int width, height;
	float time;
	int current_frame;
	std::vector<Frame> animation;
};