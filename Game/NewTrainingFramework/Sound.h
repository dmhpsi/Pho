#pragma once
#include <SFML\Audio.hpp>
#include <iostream>
#include "Globals.h"

extern float globalVolume;

class Sound
{
	sf::Sound instance;
	sf::SoundBuffer sb;
public:
	void Init(const char * path);

	int ID;

	/* Replay the sound from start */
	void Replay();

	/* Pause the sound if playing and resume it if paused */
	void PauseResume();

	/* Stop playing the sound and set playing offset to zero */
	void Stop();
};



class Music
{
	sf::Music instance;
public:
	void Init(const char * path);

	int ID;

	/* Replay the music from start */
	void Replay();

	/* Pause the music if playing and resume it if paused */
	void PauseResume();

	/* Stop playing the music and set playing offset to zero */
	void Stop();
};
