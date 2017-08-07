#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"

SceneManager* SceneManager::Instance = 0;

SceneManager* SceneManager::GetInstance()
{
	if (!Instance)
	{
		Instance = new SceneManager();
	}
	return Instance;
}

void SceneManager::Fade(bool isFadeIn,int millis)
{
	if (isFadeIn)
	{
		fadeStartTick = currentTick;
	}
	else
	{
		fadeStartTick = currentTick + millis;
	}
	fadeMillis = millis;
}

void SceneManager::Init(const char *smFile)
{
	int tmp;
	FILE *Resource;
	fopen_s(&Resource, smFile, "r");
	fscanf_s(Resource, "#Scene Width: %f\n", &sceneWidth);
	sceneHeight = sceneWidth*Globals::screenHeight / Globals::screenWidth;

	Camera::GetInstance()->SetOrtho(-sceneWidth / 2, sceneWidth / 2, -sceneHeight / 2, sceneHeight / 2, -10, 10);
	Camera::GetInstance()->speed = sceneHeight / 2;

	fscanf_s(Resource, "#Objects: %d\n", &numObject);
	listObject = new Object[numObject];
	for (int i = 0; i < numObject; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listObject[i].ID);
		fscanf_s(Resource, "MODEL %d\n", &tmp);
		listObject[i].model = (Model*)ResourceManager::GetInstance()->GetResource(OBJ_MODEL, tmp);
		fscanf_s(Resource, "TEXTURES %d\n", &listObject[i].numTextures);
		listObject[i].textures = new Texture*[listObject[i].numTextures];
		for (int j = 0; j < listObject[i].numTextures; j++)
		{
			fscanf_s(Resource, "TEXTURE %d\n", &tmp);
			listObject[i].textures[j] = (Texture*)ResourceManager::GetInstance()->GetResource(OBJ_TEXTURE, tmp);
		}
		
		fscanf_s(Resource, "MSPF %d\n", &listObject[i].mspf);

		fscanf_s(Resource, "SHADER %d\n", &tmp);
		listObject[i].shader = (Shaders*)ResourceManager::GetInstance()->GetResource(OBJ_SHADER, tmp);

		char link[10];
		float z;
		fscanf(Resource, "TYPE %s\n", link);
		if (strcmp(link, "BG_OBJ") == 0)
		{
			listObject[i].type = BG_OBJ;
		}
		else if (strcmp(link, "MAN_OBJ") == 0)
		{
			listObject[i].type = MAN_OBJ;
		}
		else if (strcmp(link, "PHO_OBJ") == 0)
		{
			listObject[i].type = PHO_OBJ;
		}
		else if (strcmp(link, "SKY_OBJ") == 0)
		{
			listObject[i].type = SKY_OBJ;
		}

		fscanf_s(Resource, "POSITION %f, %f\n", &listObject[i].x, &listObject[i].y);
		listObject[i].T.SetTranslation(listObject[i].x, listObject[i].y, listObject[i].type);
		fscanf_s(Resource, "ROTATION %f\n", &listObject[i].angle);
		listObject[i].angle *= PI / 180;
		listObject[i].R.SetRotationZ(listObject[i].angle);

		fscanf_s(Resource, "SIZE %f, %f\n", &listObject[i].w, &listObject[i].h);
		listObject[i].S.SetScale(0.5*listObject[i].w, 0.5*listObject[i].h, 1);
	}

	fadeMillis = 0;
	fadeStartTick = 0;
}

void SceneManager::Draw(int numDrawObjects, ...)
{
	if (fadeMillis > 0 && isFading)
	{
		float ratio = (float(currentTick - fadeStartTick) / fadeMillis);
		if (ratio < 0 && ratio > -0.04)
		{
			isFading = false;
			ratio = 0;
		}
		if (ratio > 1)
		{
			ratio = 1;
			isFaded = true;
		}
		else
		{
			isFaded = false;
		}

		globalFadeRatio = abs(ratio);
	}

	if (numDrawObjects <= 0)
	{
		for (int i = 0; i < numObject; i++)
		{
			listObject[i].Draw();
		}
	}
	else
	{
		va_list obj_list;
		va_start(obj_list, numDrawObjects);
		for (int i = 0; i < numDrawObjects; i++)
		{
			int tmp = va_arg(obj_list, int);
			for (int j = 0; j < numObject; j++)
			{
				if (tmp == listObject[j].ID)
				{
					listObject[j].Draw();
					break;
				}
			}
		}
		va_end(obj_list);
	}
}


void SceneManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}

SceneManager::~SceneManager()
{
	delete[] listObject;
}

