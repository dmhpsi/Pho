#pragma once
#include "Box2D/Box2D.h"
#include "FloorObject.h"
#include "IngredientObject.h"
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

	b2WeldJointDef weldJointDef;
	int m_inumOfFloor = 10;
	int currentFloor;
	const float baseSpeed = 15.0f;
	float objSpeed = baseSpeed;
	b2Fixture* m_platform;
	b2BodyDef bodyDef;
	std::vector<FloorObject*> floorObj;
	IngredientObject* objBody;
	bool m_button;
	bool m_needMoveFloor;

	void Init();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void Keyboard(int key);
	int getCurrentFloor(b2Body* b1);
	void Update(float dt);
};