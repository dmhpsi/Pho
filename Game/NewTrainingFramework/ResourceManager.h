#pragma once

#include "Model.h"
#include "Texture.h"
#include "Vertex.h"
#include "Shaders.h"
#include <SFML\Audio.hpp>
#include <vector>
using namespace std;

class ResourceManager
{
private:
	static ResourceManager* Instance;
	~ResourceManager();
public:
	void Init(const char* rmFile);
	static ResourceManager* GetInstance();
	static void CleanInstance();
	void* GetResource(MyEnum type, int ID);

	int numModels;
	Model* listModels;

	int numTextures;
	Texture* listTextures;

	int numShaders;
	Shaders* listShaders;

	int numScenes;
	int* sceneIDs;
	char** listScenes;

	int numSounds;
	int* soundBufferIDs;
	sf::SoundBuffer* listSoundBuffers;
	sf::Sound soundInstance;

	int numMusics;
	int* musicIDs;
	char** listMusic;
	sf::Music musicInstance;

	int numFonts;
};