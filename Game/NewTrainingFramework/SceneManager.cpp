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

void SceneManager::Init(const char *smFile)
{
	int tmp;
	FILE *Resource;
	fopen_s(&Resource, smFile, "r");
	fscanf_s(Resource, "#Scene Width: %f\n", &sceneWidth);
	sceneHeight = sceneWidth*Globals::screenHeight / Globals::screenWidth;

	Camera::GetInstance()->SetOrtho(-sceneWidth / 2, sceneWidth / 2, -sceneHeight / 2, sceneHeight / 2, -1, 1);
	Camera::GetInstance()->speed = sceneHeight / 2;

	fscanf_s(Resource, "#Backgrounds: %d\n", &numBg);
	fscanf_s(Resource, "#Objects: %d\n", &numObject);
	listObject = new Object[numObject + numBg];
	for (int i = 0; i < numObject + numBg; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listObject[i].ID);
		fscanf_s(Resource, "MODEL %d\n", &tmp);
		listObject[i].model = (Model*)ResourceManager::GetInstance()->GetResource(OBJ_MODEL, tmp);
		fscanf_s(Resource, "TEXTURES %d\n", &listObject[i].numTextures);

		if (listObject[i].numTextures > 0)
		{
			fscanf_s(Resource, "TEXTURE %d\n", &tmp);
			listObject[i].listTextures = (Texture*)ResourceManager::GetInstance()->GetResource(OBJ_TEXTURE, tmp);
		}
		fscanf_s(Resource, "MSPF %d\n", &listObject[i].mspf);

		fscanf_s(Resource, "SHADER %d\n", &tmp);
		listObject[i].shader = (Shaders*)ResourceManager::GetInstance()->GetResource(OBJ_SHADER, tmp);

		Matrix s, t, r;
		float x, y, z;
		fscanf_s(Resource, "POSITION %f, %f, %f\n", &x, &y, &z);
		t.SetTranslation(x, y, z);
		fscanf_s(Resource, "ROTATION %f\n", &x);
		x *= PI / 180;
		r.SetRotationZ(x);

		fscanf_s(Resource, "SCALE %f\n", &x);
		fscanf_s(Resource, "SIZE %f, %f\n", &listObject[i].w, &listObject[i].h);
		x *= listObject[i].w / 2;
		s.SetScale(x, x*listObject[i].h / listObject[i].w, 1);
		listObject[i].W = s*r*t;
	}
}

void SceneManager::Draw(int binaryPos)
{
	int idx = 0;
	if (binaryPos < 0)
	{
		for (int i = 0; i < numBg + numObject; i++)
			listObject[i].Draw();
	}
	else
	{
		while (binaryPos > 0)
		{
			if (binaryPos & 1)
				listObject[idx].Draw();
			binaryPos >> 1;
			idx++;
			if (idx >= numBg + numObject)
				break;
		}
	}
}

void SceneManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}

SceneManager::~SceneManager()
{
	delete []listObject;
}

