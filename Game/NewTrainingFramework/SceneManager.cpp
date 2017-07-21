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
	fscanf_s(Resource, "#Objects: %d\n", &numObject);
	listObject = new Object[numObject];
	for (int i = 0; i < numObject; i++)
	{
		fscanf_s(Resource, "ID %d\n", &listObject[i].ID);
		fscanf_s(Resource, "MODEL %d\n", &tmp);
		listObject[i].model = (Model*)ResourceManager::GetInstance()->GetObjPart(OBJ_MODEL, tmp);
		fscanf_s(Resource, "TEXTURES %d\n", &listObject[i].numTextures);

		tmp = -1237841278;
		if (listObject[i].numTextures > 0)
		{
			listObject[i].listTextures = new Texture*[listObject[i].numTextures];
			for (int j = 0; j < listObject[i].numTextures; j++)
			{
				fscanf_s(Resource, "TEXTURE %d\n", &tmp);
				listObject[i].listTextures[j] = (Texture*)ResourceManager::GetInstance()->GetObjPart(OBJ_TEXTURE, tmp);
			}
		}
		else
		{
			listObject[i].listTextures = new Texture*[1];
		}
		fscanf_s(Resource, "CUBETEXTURES %d\n", &tmp);
		if (tmp == 1)
		{
			fscanf_s(Resource, "CUBETEX %d\n", &tmp);
			listObject[i].listTextures[0] = (Texture*)ResourceManager::GetInstance()->GetObjPart(OBJ_SKY_TEXTURE, tmp);
		}
		
		fscanf_s(Resource, "SHADER %d\n", &tmp);
		listObject[i].shader = (Shaders*)ResourceManager::GetInstance()->GetObjPart(OBJ_SHADER, tmp);

		fscanf_s(Resource, "LIGHTS %d\n", &tmp);
		for (int j = 0; j < tmp; j++)
		{
			int t;
			fscanf_s(Resource, "LIGHT %d\n", &t);
		}
		Matrix s, t, rx, ry, rz;
		float x, y, z;
		fscanf_s(Resource, "POSITION %f, %f, %f\n", &x, &y, &z);
		//t.SetTranslation(x, y, z);
		t.SetTranslation(x, y, z);
		fscanf_s(Resource, "ROTATION %f, %f, %f\n", &x, &y, &z);
		x *= PI / 180;
		y *= PI / 180;
		z *= PI / 180;
		rx.SetRotationX(x);
		ry.SetRotationY(y);
		rz.SetRotationZ(z);

		fscanf_s(Resource, "SCALE %f, %f, %f\n", &x, &y, &z);
		//s.SetScale(x, y, z);
		s.SetScale(x,
			x * listObject[i].listTextures[0]->height / listObject[i].listTextures[0]->width,
			1);
		listObject[i].W = rx*s*t;
	}
}

void SceneManager::Draw(int numDrawObjects, ...)
{
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

