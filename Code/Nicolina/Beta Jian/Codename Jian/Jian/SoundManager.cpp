//SoundManager.cpp

#include "stdafx.h"

#include "SoundManager.h"

SoundManager::SoundManager()
{

}

bool SoundManager::Initialise(const std::string &sound_directory)
{
	directory = sound_directory;

	return true;
}

void SoundManager::Cleanup()
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = sound_buffers.begin();
	while(it != sound_buffers.end())
	{
		delete it->second;
		it->second = nullptr;
		++it;
	}

	sound_buffers.clear();
}

sf::Sound* SoundManager::Load(const std::string file_name)
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = sound_buffers.find(file_name);

	//No such file already in map?
	if(it == sound_buffers.end())
	{
		if(!LoadSound(file_name))
		{
			return nullptr;
		}

		it = sound_buffers.find(file_name);
	}

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*it->second);

	return sound;
}

bool SoundManager::LoadSound(const std::string file_name)
{
	std::string file_path = directory + file_name;

	sf::SoundBuffer* sound_buffer = new sf::SoundBuffer();
	sound_buffer->loadFromFile(file_path);
	
	if(sound_buffer == nullptr)
	{
		return false;
	}

	sound_buffers.insert(std::pair<std::string, sf::SoundBuffer*>(file_name, sound_buffer));
	return true;
}