#include "stdafx.h"
#include "PhysicManager.h"
#include "..\NewTrainingFramework\SceneManager.h"

#include <stdio.h>
#include <iostream>

//extern 	Object* listObject;
float PixelToMeter(float pixel)
{
	return pixel / 100;
}
float MeterToPixel(float meter)
{
	return meter * 100;
}
PhysicManager* PhysicManager::Instance = 0;
PhysicManager::PhysicManager()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -40.0f);
	m_world = new b2World(gravity);
	m_world->SetContactListener(this);
	b2BodyDef bodyDef;
	m_groundBody = m_world->CreateBody(&bodyDef);
}
PhysicManager* PhysicManager::GetInstance()
{
	if (!Instance)
	{
		Instance = new PhysicManager();
	}
	return Instance;
}

void PhysicManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}
PhysicManager::~PhysicManager()
{
	for (int i = 0; i < floorObj.size(); i++)
	{
		delete floorObj[i];
	}
	delete objBody;
	delete m_world;
	m_world = NULL;
}

void PhysicManager::Init()
{
	//Create object for each floor
	for (int i = 0; i < 6; i++)
	{
		FloorObject* obj = new FloorObject(m_world, i);
		obj->m_body->SetUserData(&SceneManager::GetInstance()->listObject[i+6]);
		obj->m_platform->SetUserData(&SceneManager::GetInstance()->listObject[i]);
		//obj->m_body->SetUserData(&SceneManager::GetInstance()->listObject[i]);
		
		floorObj.push_back(obj);
	}

	//Create PHO INGREDIENT
	{
		objBody = new IngredientObject(m_world);
		objBody->m_body->SetUserData(&SceneManager::GetInstance()->listObject[12]);
	}

	m_button = false;
	m_needMoveFloor = false;
}

void PhysicManager::Keyboard(int key)
{
	switch (key)
	{
	case 0x41:
		std::cout << "GLFW_KEY_A" << std::endl;
		m_button = true;
		break;
	}
}

int PhysicManager::getCurrentFloor(b2Body* b1)
{
	for (int i = 0; i < floorObj.size(); i++)
	{
		if (b1 == floorObj[i]->m_body)
		{
			return floorObj[i]->m_iobjLevel;
		}
	}
}

void PhysicManager::BeginContact(b2Contact* contact)
{
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Shape::Type bodyType1 = contact->GetFixtureA()->GetShape()->m_type;
	b2Shape::Type bodyType2 = contact->GetFixtureB()->GetShape()->m_type;

	b2Body* b2 = contact->GetFixtureB()->GetBody();
	currentFloor = getCurrentFloor(b1);
	objSpeed = baseSpeed + (currentFloor / 1)*0.5;
	void* bodyAUserData = b1->GetUserData();
	void* bodyBUserData = b2->GetUserData();
	int x = b1->GetType();
	int y = b2->GetType();
	//check whether body1 is floorObject and body2 is PhoIngredient, weldJoint is not created
	if (x == 1 && y == 2
		&& bodyType1 == 1 && bodyType2 == 2
		&& weldJointDef.userData == nullptr)
	{
		std::cout << "Cham" << std::endl;
		int x = objSpeed - (rand() % 2) * objSpeed * 2;
		b1->SetLinearVelocity(b2Vec2(x, 0.0f));
		if (x > 0)
		{
			((Object*)b1->GetUserData())->SetFlip(true);
		}
		else
		{
			((Object*)b1->GetUserData())->SetFlip(false);
		}
		b2Vec2 worldCoordsAnchorPoint = b2->GetWorldPoint(b2Vec2(0.6f, 0));
		weldJointDef.bodyA = b1;
		weldJointDef.bodyB = b2;
		b2Vec2 edgePos = weldJointDef.bodyB->GetLocalPoint(worldCoordsAnchorPoint);
		weldJointDef.localAnchorB = edgePos;
		edgePos.y += 2.51f;
		weldJointDef.localAnchorA = edgePos;
		weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
		weldJointDef.userData = "canTao";
	}
}

void PhysicManager::EndContact(b2Contact* contact)
{
	weldJointDef.userData = nullptr;
}

void PhysicManager::Update(float dt)
{
	m_timeStep = dt;
	m_velocityIterations = 6;
	m_positionIterations = 2;
	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

	static b2WeldJoint* weldJoint = nullptr;
	if (weldJointDef.bodyA != nullptr)
	{
		if (weldJointDef.userData == "canTao")
		{
			// Catch
			weldJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
			weldJointDef.userData = "daTao";
			weldJointDef.bodyA = nullptr;
			m_needMoveFloor = true;

			Camera::GetInstance()
				->SetHeight(floorObj[(currentFloor + 1) % 6]
					->m_body->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth, 1000);

			((Object*)floorObj[(currentFloor) % 5]->m_body->GetUserData())->SetStatus(OBJ_RUN);
			((Object*)objBody->m_body->GetUserData())->SetVisible(false, 100);
		}
	}
	else if (m_button && weldJoint != nullptr && objBody->m_body->GetLinearVelocity().y == 0)
	{
		// Throw
		m_world->DestroyJoint(weldJoint);
		weldJoint = nullptr;
		float impulse = objBody->m_body->GetMass() * 0.2;
		objBody->m_body->ApplyLinearImpulse(b2Vec2(-2.1*objBody->m_body->GetLinearVelocity().x, 105), objBody->m_body->GetWorldCenter(), true);
		std::cout << "currentFloor: " << currentFloor << std::endl;
		((Object*)floorObj[(currentFloor) % 5]->m_body->GetUserData())->SetStatus(OBJ_IDLE);
		m_button = false;
	}

	else if (m_needMoveFloor && objBody->m_body->GetLinearVelocity().y == 0 && currentFloor > 2)
	{

		int floorToBeRemoved = currentFloor - 3;
		int floorToBeUpdated = currentFloor + 3;
		if (currentFloor == 1)
		{
			floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);

		}
		else
		{
			floorObj[floorToBeRemoved % 6]->m_platform->SetTransform(b2Vec2(0, m_floorHeight*(floorToBeUpdated)), 0);
			floorObj[floorToBeRemoved % 6]->m_body->SetTransform(b2Vec2(RandomFloat(-m_floorWidth / 2 + 4, m_floorWidth / 2 - 4), m_floorHeight*(currentFloor + 3) + 0.5 + floorObj[0]->m_objLength), 0);
			floorObj[floorToBeRemoved % 6]->m_iobjLevel = floorToBeUpdated;
			floorObj[floorToBeRemoved % 6]->m_body->SetAwake(false);
			floorObj[floorToBeRemoved % 6]->m_body->SetActive(true);
			floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);
			//floorObj[(floorToBeRemoved+1) % 6]->m_body->SetActive(false);
		}
		m_needMoveFloor = false;

	}
	if (objBody->m_body->GetLinearVelocity().y > 0)
	{
		b2Fixture* fixture = floorObj[(currentFloor + 1) % 6]->m_body->GetFixtureList();
		b2Filter filter = fixture->GetFilterData();
		filter.groupIndex = k_largeGroup;
		fixture->SetFilterData(filter);
	}
	else if (objBody->m_body->GetLinearVelocity().y <= 0)
	{
		b2Fixture* fixture = floorObj[(currentFloor + 1) % 6]->m_body->GetFixtureList();
		b2Filter filter = fixture->GetFilterData();
		filter.groupIndex = k_smallGroup;
		fixture->SetFilterData(filter);
	}
	for (int i = 0; i<floorObj.size(); i++)
	{
		b2Vec2 vel = floorObj[i]->m_body->GetLinearVelocity();
		if (floorObj[i]->m_body->GetPosition().x < -m_floorWidth / 2 + 2)
		{
			vel.x = objSpeed;
			((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(true);
		}
		else if (floorObj[i]->m_body->GetPosition().x > m_floorWidth / 2 - 2)
		{
			vel.x = -objSpeed;
			((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(false);
		}
		floorObj[i]->m_body->SetLinearVelocity(vel);
	}

	b2Body* b = m_world->GetBodyList();
	m_world->GetBodyCount();
	Object* listObject = SceneManager::GetInstance()->listObject;
	//while (b != NULL)
	while(b->GetUserData()!=NULL)
	{
		if (b->GetType() == 0)
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth + 23);
		}
		if (b->GetType() == 1 )
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth);
		}
		if (b->GetType() == 2)
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth);
		}
		b = b->GetNext();
	}
	m_button = false;
	m_button = false;
}

