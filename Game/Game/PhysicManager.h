#pragma once
#include "Box2D/Box2D.h"
#include "FloorObject.h"
#include "IngredientObject.h"
#include "StateMachine.h"
#include "def.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "../NewTrainingFramework/NewTrainingFramework.h"

class PhysicManager : public b2ContactListener
{
private:
	static PhysicManager* Instance;
	PhysicManager();
	~PhysicManager();
public:
	static PhysicManager* GetInstance();
	static void CleanInstance();
	b2Body* m_groundBody;
	b2World* m_world;
	//void Update();
	float32 m_timeStep;
	int32 m_velocityIterations;
	int32 m_positionIterations;
	bool endGame;

	int numParticle;
	Object* listParticle;

	b2WeldJointDef weldJointDef;
	int m_inumOfFloor;
	int currentFloor;
	float baseSpeed;
	float objSpeed = baseSpeed;
	b2Fixture* m_platform;
	std::vector<FloorObject*> floorObj;
	FloorObject* lastFloor;
	IngredientObject* objBody;
	int m_ilevel;
	bool m_button;
	bool m_needMoveFloor;
	void Init(const char* physicsFile);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void Keyboard(int key);
	void MouseClick();
	int getCurrentFloor(b2Body* b1);
	void Update(float dt);
};