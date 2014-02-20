//HeadsUpDisplay.h

#pragma once

class HeadsUpDisplay
{
public:
	HeadsUpDisplay();

	bool Initialise(SpriteManager* sprite_mgr);
	void Cleanup();

	void DrawHUD(sf::RenderWindow* window);
	void Update(float deltatime);

	//move the HUD with the designated x and y values
	void Move(float x, float y);

	//Move the arrow to the designated Type
	void MoveArrow(Type type);

	//Add/delete Elemental point
	void AddElementalPoint(Type element_type);
	void DeleteElementalPoint(Type element_type);

private:
	AnimatedSprite* hud_arrow;
	std::vector<AnimatedSprite*> symbols;

	SpriteManager* sprite_manager;

	std::vector<AnimatedSprite*> fire_points;
	std::vector<AnimatedSprite*> water_points;
	std::vector<AnimatedSprite*> wood_points;

	float current_fire_pos;
	float current_water_pos;
	float current_wood_pos;
};

