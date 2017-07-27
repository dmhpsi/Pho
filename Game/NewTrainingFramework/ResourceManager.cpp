#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager* ResourceManager::Instance = 0;

ResourceManager* ResourceManager::GetInstance()
{
	if (!Instance)
	{
		Instance = new ResourceManager();
	}
	return Instance;
}

void ResourceManager::Init(const char* rmFile)
{
	char link[200], link2[200];
	FILE *Resource;
	fopen_s(&Resource, rmFile, "r");

	// assign numModels variable
	fscanf_s(Resource, "#Models: %d\n", &numModels);
	// create a list of models
	listModels = new Model[numModels];
	for (int i = 0; i < numModels; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listModels[i].ID);
		fscanf(Resource, "FILE \"%s\n", link);
		link[strlen(link) - 1] = NULL;
		listModels[i].LoadNFG(link);
	}
	
	// assign numTextures variable
	fscanf_s(Resource, "#2D Textures: %d\n", &numTextures);
	fscanf_s(Resource, "#FONTS: %d\n", &numFonts);

	// create a list of textures
	listTextures = new Texture[numTextures + numFonts];
	char mode[50];
	for (int i = 0; i < numTextures; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listTextures[i].ID);
		fscanf(Resource, "FILE \"%s\n", link);
		link[strlen(link) - 1] = NULL;
		fscanf(Resource, "FRAGS %d\n", &listTextures[i].numOfFragments);
		fscanf(Resource, "TILING %s\n", mode);
		if (strcmp("REPEAT", mode) == 0)
			listTextures[i].LoadToGPU(link, NORMAL_OBJ, GL_REPEAT);
		else
			listTextures[i].LoadToGPU(link, NORMAL_OBJ, GL_CLAMP_TO_EDGE);
	}

	// Read font type from rm.txt
	for (int i = 0; i < numFonts; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listTextures[numTextures + i].ID);
		fscanf(Resource, "FILE \"%s\n", link);
		link[strlen(link) - 1] = NULL;
		listTextures[numTextures + i].LoadToGPU(link, OBJ_FONT, GL_CLAMP_TO_EDGE);
	}

	// Number of shaders
	fscanf(Resource, "#Shaders: %d\n", &numShaders);
	listShaders = new Shaders[numShaders];
	for (int i = 0; i < numShaders; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listShaders[i].ID);
		fscanf(Resource, "VS \"%s\n", link);
		link[strlen(link) - 1] = NULL;
		fscanf(Resource, "FS \"%s\n", link2);
		link2[strlen(link2) - 1] = NULL;
		listShaders[i].Init(link, link2);
	}

	fscanf(Resource, "#Scenes: %d\n", &numScenes);
	listScenes = new char*[numScenes];
	SceneIDs = new int[numScenes];
	for (int i = 0; i < numScenes; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n",&SceneIDs[i]);
		fscanf(Resource, "FILE \"%s\n", tmp);
		tmp[strlen(tmp) - 1] = NULL;
		listScenes[i] = new char[strlen(tmp) + 1];
		memset(listScenes[i], NULL, strlen(tmp));
		memcpy(listScenes[i], tmp, strlen(tmp));
		listScenes[i][strlen(tmp)] = NULL;
	}

	// Load sound
	fscanf(Resource, "#Sounds: %d\n", &numSounds);
	listSounds = new sf::Music[numSounds];
	SoundIDs = new int[numSounds];
	for (int i = 0; i < numSounds; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n", &SceneIDs[i]);
		fscanf(Resource, "FILE \"%s\n", tmp);
		tmp[strlen(tmp) - 1] = NULL;
		if (!listSounds[i].openFromFile(tmp))
			SoundIDs[i] = -1;
	}
}

void* ResourceManager::GetResource(MyEnum type, int ID)
{
	if (type == OBJ_MODEL)
	{
		for (int i = 0; i < numModels; i++)
		{
			if (listModels[i].ID == ID)
				return &listModels[i];
		}
	}
	else if (type == OBJ_TEXTURE)
	{
		for (int i = 0; i < numTextures; i++)
		{
			if (listTextures[i].ID == ID)
				return &listTextures[i];
		}
	}
	else if (type == OBJ_SHADER)
	{
		for (int i = 0; i < numShaders; i++)
		{
			if (listShaders[i].ID == ID)
				return &listShaders[i];
		}
	}
	else if (type == SCENE)
	{
		for (int i = 0; i < numScenes; i++)
		{
			if (SceneIDs[i] == ID)
				return listScenes[i];
		}
	}
	return 0;
}

void ResourceManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}

ResourceManager::~ResourceManager()
{   
	delete[] listModels;
	delete[] listShaders;
	delete[] listTextures;
	delete []SceneIDs;
	for (int i = 0; i < numScenes; i++)
		delete listScenes[i];
	delete[] listScenes;
	for (int i = 0; i < numSounds; i++)
		if (listSounds[i].getStatus() == sf::Music::Playing)
			listSounds[i].stop();

	// Cause memory corruption if deleted
	//delete[] listSounds;
	delete[] SoundIDs;
}
