#pragma once
#include "Box2D/Box2D.h"

class PhysicManager
{
private:
	static PhysicManager* Instance;
	PhysicManager();
	~PhysicManager();
public:
	void Init(const char* rmFile);
	static PhysicManager* GetInstance();
	static void CleanInstance();
	b2Body* m_groundBody;
	b2World* m_world;
	void Update();

};