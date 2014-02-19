//HeadsUpDisplay.h

#pragma once

class HeadsUpDisplay
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();

	bool Initialise(SpriteManager* sprite_mgr);
	void Cleanup();

	void DrawHUD(sf::RenderWindow* window);
	void Update(float deltatime);

private:
	AnimatedSprite* hud_arrow;
	std::vector<AnimatedSprite*> symbols;

	AnimatedSprite* fire_template;
	AnimatedSprite* water_template;
	AnimatedSprite* wood_template;

	std::vector<AnimatedSprite*> fire_points;
	std::vector<AnimatedSprite*> water_points;
	std::vector<AnimatedSprite*> wood_points;
};

