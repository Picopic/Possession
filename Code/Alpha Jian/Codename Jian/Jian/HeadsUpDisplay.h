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

	//Move the indicator to the designated Type
	void MoveIndicator(Type type);

	//Add/delete Elemental point
	void AddElementalPoint(Type element_type);
	void DeleteElementalPoint(Type element_type);

	//Empty points
	void AddEmptyPoint(Type element_type);
	void DeleteEmptyPoint(Type element_type);

private:
	std::vector<AnimatedSprite*> hud_indicator;
	AnimatedSprite* current_indicator;
	std::vector<AnimatedSprite*> symbols;

	SpriteManager* sprite_manager;

	std::vector<AnimatedSprite*> fire_points;
	std::vector<AnimatedSprite*> water_points;
	std::vector<AnimatedSprite*> wood_points;

	//Empty points
	std::vector<AnimatedSprite*> empty_fire;
	std::vector<AnimatedSprite*> empty_water;
	std::vector<AnimatedSprite*> empty_wood;

	float current_empty_fire;
	float current_empty_water;
	float current_empty_wood;

	//the position of the last elemental point
	float current_fire_pos;
	float current_water_pos;
	float current_wood_pos;

	//Offset between elemental points
	float x_offset;
	float y_offset;

	//The size of the symbols sides
	int symbol_height;
	int symbol_width;
};

