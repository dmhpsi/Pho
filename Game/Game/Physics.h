#pragma once
#include "Box2D/Box2D.h"
#include "FloorObject.h"
#include "IngredientObject.h"
#include <vector>
class Physics : public b2ContactListener
{
public:
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

	void Init(b2World* world);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void Keyboard(int key);
	int getCurrentFloor(b2Body* b1);
	void Update(b2World* m_world);
};