#include "stdafx.h"
#include "Sound.h"

void Sound::Init(const char * path)
{
	sb.loadFromFile(path);
	instance.setBuffer(sb);
}

void Sound::Replay()
{
	instance.setVolume(globalVolume);
	instance.setPlayingOffset(sf::seconds(0));
	instance.play();
}

void Sound::PauseResume()
{
	instance.setVolume(globalVolume);
	if (instance.getStatus() == sf::Sound::Playing)
	{
		instance.pause();
	}
	else
	{
		instance.play();
	}
}

void Sound::Stop()
{
	instance.stop();
}

void Music::Init(const char * path)
{
	instance.openFromFile(path);
	instance.setLoop(true);
}

void Music::Replay()
{
	instance.setVolume(globalVolume);
	instance.setPlayingOffset(sf::seconds(0));
	instance.play();
}

void Music::PauseResume()
{
	instance.setVolume(globalVolume);
	if (instance.getStatus() == sf::Music::Playing)
	{
		instance.pause();
	}
	else
	{
		instance.play();
	}
}

void Music::Stop()
{
	instance.stop();
}
