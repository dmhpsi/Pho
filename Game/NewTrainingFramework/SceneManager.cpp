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

void SceneManager::Fade(bool isFadeIn, int millis)
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

bool compareZ(int2 id1, int2 id2)
{
	return id1.y < id2.y;
}

void SceneManager::Init(const char *smFile)
{
	int tmp;
	FILE *Resource;
	fopen_s(&Resource, smFile, "r");
	fscanf_s(Resource, "#Scene Width: %f\n", &sceneWidth);
	sceneHeight = sceneWidth*Globals::screenHeight / Globals::screenWidth;

	Camera::GetInstance()->SetOrtho(-sceneWidth / 2, sceneWidth / 2, -sceneHeight / 2, sceneHeight / 2, -1, 1);
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
			// If it is win texture
			if (tmp == 18)
			{
				winTextureId = i;
				continue;
			}
			// If it is lose texture
			if (tmp == 25)
			{
				loseTextureId = i;
				continue;
			}
			// If it is home button
			if (tmp == 20)
			{
				homeButtonId = i;
				continue;
			}
			// If it is resume button
			if (tmp == 21)
			{
				resumeButtonId = i;
			}
			// If it is replay button
			if (tmp == 23)
			{
				replayButtonId = i;
			}
			// If it is next button
			if (tmp == 24)
			{
				nextButtonId = i;
			}
			// Mask Id
			if (tmp == 26)
			{
				maskId = i;
			}
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
		else if (strcmp(link, "PAR_OBJ") == 0)
		{
			listObject[i].type = PAR_OBJ;
		}
		else if (strcmp(link, "UI_OBJ") == 0)
		{
			listObject[i].type = UI_OBJ;
		}

		int2 tmp;
		tmp.x = i;
		tmp.y = listObject[i].type;

		drawOrder.push_back(tmp);

		fscanf_s(Resource, "POSITION %f, %f\n", &listObject[i].x, &listObject[i].y);
		listObject[i].T.SetTranslation(listObject[i].x, listObject[i].y, 0);
		fscanf_s(Resource, "ROTATION %f\n", &listObject[i].angle);
		listObject[i].angle *= PI / 180;
		listObject[i].R.SetRotationZ(listObject[i].angle);

		fscanf_s(Resource, "SIZE %f, %f\n", &listObject[i].w, &listObject[i].h);
		listObject[i].S.SetScale(0.5*listObject[i].w, 0.5*listObject[i].h, 1);
	}

	std::sort(drawOrder.begin(), drawOrder.end(), compareZ);

	// disable home button, resume button and win button
	/*listObject[winTextureId].SetVisible(true, 0);
	listObject[homeButtonId].SetVisible(true, 0);
	listObject[resumeButtonId].SetVisible(true, 0);*/

	fadeMillis = 0;
	fadeStartTick = 0;
}

void SceneManager::Draw(int numDrawObjects, ...)
{
	if (fadeMillis > 0)
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
		for (int i = 0; i < drawOrder.size(); i++)
		{
			listObject[drawOrder[i].x].Draw();
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

