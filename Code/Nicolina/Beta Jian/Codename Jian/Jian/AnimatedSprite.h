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
	AnimatedSprite();

	AnimatedSprite(sf::Texture* spritesheet, int width, int height, int x, int y);

	sf::Sprite* getSprite();

	void Update(float deltatime);
	void AddFrame(Frame &frame);
	int GetNumberOfFrames();
	float GetFrameDuration();
	bool IsLastFrame();
	
	void StopAnimation();
	void StartAnimation();

	int GetCurrentFrame();
	void SetCurrentFrame(int frame);

private:
	bool PlayAnimation;

	sf::Sprite* image;
	sf::Texture* spritesheet;
	float x, y;
	int width, height;
	float time;
	int current_frame;
	std::vector<Frame> animation;
};