//SoundManager.h

#pragma once

class SoundManager
{
public:
	SoundManager();

	bool Initialise(const std::string &sound_directory);
	void Cleanup();

	sf::Sound* Load(const std::string file_name);

	void GetSoundBuffer(std::string file_name);

private:
	bool LoadSound(const std::string file_name);

	std::map<std::string, sf::SoundBuffer*> sound_buffers;
	std::string directory;
};