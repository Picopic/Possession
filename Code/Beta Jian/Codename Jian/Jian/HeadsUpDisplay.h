//HeadsUpDisplay.h

#pragma once

class ConfigManager;

class HeadsUpDisplay
{
public:
	HeadsUpDisplay();

	bool Initialise(SpriteManager* sprite_mgr);
	void Cleanup();

	void DrawHUD(sf::RenderWindow* window);
	void Update(float deltatime);

	//Restart the HUD
	void Restart();

	//move the HUD with the designated x and y values
	void Move(float x, float y);

	//Move the indicator to the designated Type
	void MoveIndicator(Type type);

	//Add the values
	void AddElements(sf::Vector3i elements);
	//Delete the values
	void DeleteElements(sf::Vector3i elements);

	//Add a soul
	void AddSoul();
	//Delete a soul
	void DeleteSoul();

private:
	float sprite_width, sprite_height;

	//Number of different images in the HUD spritesheet
	int NumberOfImages;

	//Inactive symbols
	std::vector<AnimatedSprite*> InactiveFireSymbols;
	std::vector<AnimatedSprite*> InactiveWaterSymbols;
	std::vector<AnimatedSprite*> InactiveWoodSymbols;

	//Active symbols
	std::vector<AnimatedSprite*> ActiveFireSymbols;
	std::vector<AnimatedSprite*> ActiveWaterSymbols;
	std::vector<AnimatedSprite*> ActiveWoodSymbols;

	//Dead symbols
	AnimatedSprite* DeadFire;
	AnimatedSprite* DeadWater;
	AnimatedSprite* DeadWood;
	bool deadfire, deadwater, deadwood;

	//Predefined symbol positions
	sf::Vector2f position[3];

	//Active element
	Type ActiveElement;

	//Current number of points in symbols
	int fire, water, wood;

	//Souls
	float SoulXPos;
	float SoulYPos;
	std::vector<AnimatedSprite*> Souls;
	int SoulWidth;
	int SoulHeight;

	//Input from files
	ConfigManager* m_ConfigManager;
	//Loading sprites
	SpriteManager* m_SpriteManager;
};

