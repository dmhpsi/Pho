#include "stdafx.h"
#include "ResourceManager.h"

<<<<<<< HEAD
sf::Music *b;
=======
>>>>>>> dmhpsi/huynx

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
<<<<<<< HEAD
	fscanf_s(Resource, "#FONTS: %d\n", &numFonts);

	// create a list of textures
	listTextures = new Texture[numTextures + numFonts];
=======
	// create a list of textures
	listTextures = new Texture[numTextures];
>>>>>>> dmhpsi/huynx
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

<<<<<<< HEAD
	// Read font type from rm.txt
	for (int i = 0; i < numFonts; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listTextures[numTextures + i].ID);
		fscanf(Resource, "FILE \"%s\n", link);
		link[strlen(link) - 1] = NULL;
		listTextures[numTextures + i].LoadToGPU(link, OBJ_FONT, GL_CLAMP_TO_EDGE);
	}

=======
>>>>>>> dmhpsi/huynx
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

<<<<<<< HEAD
	fscanf(Resource, "#Scenes: %d\n", &numScenes);
	listScenes = new char*[numScenes];
	sceneIDs = new int[numScenes];
	for (int i = 0; i < numScenes; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n",&sceneIDs[i]);
=======
	// Number of Scenes
	//fscanf(Resource, "#Scenes: %d\n", &numScenes);
	////char** linkTest;
	//linkTest = new char *[numScenes];
	//ids = new int[numScenes];
	//for (int i = 0; i < numScenes; i++)
	//{
	//	linkTest[i] = new char[200];
	//	fscanf_s(Resource, "ID %d\n",&ids[i]);
	//	fscanf(Resource, "FILE \"%s\n", linkTest[i]);
	//	linkTest[i][strlen(linkTest[i]) - 1] = NULL;
	//	//link[strlen(link) - 1] = NULL;
	//	listScenes.push_back(linkTest[i]);
	//}
	//fclose(Resource);

	fscanf(Resource, "#Scenes: %d\n", &numScenes);
	listScenes = new char*[numScenes];
	ids = new int[numScenes];
	for (int i = 0; i < numScenes; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n",&ids[i]);
>>>>>>> dmhpsi/huynx
		fscanf(Resource, "FILE \"%s\n", tmp);
		tmp[strlen(tmp) - 1] = NULL;
		listScenes[i] = new char[strlen(tmp) + 1];
		memset(listScenes[i], NULL, strlen(tmp));
		memcpy(listScenes[i], tmp, strlen(tmp));
		listScenes[i][strlen(tmp)] = NULL;
	}
<<<<<<< HEAD

	// Load sound fx
	fscanf(Resource, "#Sounds: %d\n", &numSounds);
	listSounds = new Sound[numSounds];

	for (int i = 0; i < numSounds; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n", &listSounds[i].ID);
		fscanf(Resource, "FILE \"%s\n", tmp);
		tmp[strlen(tmp) - 1] = NULL;
		listSounds[i].Init(tmp);
	}

	//Load musics
	fscanf(Resource, "#Musics: %d\n", &numMusics);
	listMusics = new Music[numMusics];

	for (int i = 0; i < numMusics; i++)
	{
		char tmp[500];
		fscanf_s(Resource, "ID %d\n", &listMusics[i].ID);
		fscanf(Resource, "FILE \"%s\n", tmp);
		tmp[strlen(tmp) - 1] = NULL;
		listMusics[i].Init(tmp);
	}
	fclose(Resource);
=======
>>>>>>> dmhpsi/huynx
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
<<<<<<< HEAD
			if (sceneIDs[i] == ID)
=======
			if (ids[i] == ID)
>>>>>>> dmhpsi/huynx
				return listScenes[i];
		}
	}
	return 0;
}

<<<<<<< HEAD

=======
>>>>>>> dmhpsi/huynx
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
<<<<<<< HEAD
	delete []sceneIDs;
	for (int i = 0; i < numScenes; i++)
		delete listScenes[i];
	delete[] listScenes;

	// Cause memory corruption if deleted
	delete[] listSounds;
	delete[] listMusics;
}
=======
	delete []ids;
	for (int i = 0; i < numScenes; i++)
		delete listScenes[i];
	delete[] listScenes;
	
}
>>>>>>> dmhpsi/huynx
