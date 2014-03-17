//WaveSystem.h

#pragma once

//Forward declard classes
class ObjectWave;

class ConfigManager;

class WaveSystem
{
public:
	//Constructor that handles basic initiation
	WaveSystem();
	//Destructor that handles the cleanup
	~WaveSystem();

	//Initalise takes care of initialising the more
	//essential components
	bool Initalise(ConfigManager* ConfigMgr);
private:
	//The length of a one wave
	float Width;

	//Reading from files
	ConfigManager* m_ConfigManager;

	//Vectors of arrays
	std::vector<ObjectWave*> ObjectWaves;
};