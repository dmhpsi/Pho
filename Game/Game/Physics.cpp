#include "stdafx.h"
#include "Physics.h"
#include "define.h"
#include <iostream>


void Physics::Init(b2World* world)
{
	objBody  = new IngredientObject(world);
	//Create object for each floor
	for (int i = 0; i < 5; i++)
	{
		FloorObject* obj = new FloorObject(world, i);
		obj->m_body->SetUserData(this);
		floorObj.push_back(obj);
	}

	//Create PHO INGREDIENT
	{
		objBody->m_body->SetUserData(this);

	}

	m_button = false;
	m_needMoveFloor = false;
}

void Physics::Keyboard(int key)
	{
		switch (key)
		{
		case 'A':
			std::cout << "GLFW_KEY_A" << std::endl;
			m_button = true;
			break;
		}
	}

	int Physics::getCurrentFloor(b2Body* b1)
	{
		for (int i = 0; i < floorObj.size(); i++)
		{
			if (b1 == floorObj[i]->m_body)
			{
				return floorObj[i]->m_iobjLevel;
			}
		}
	}

	void Physics::BeginContact(b2Contact* contact)
	{
		b2Body* b1 = contact->GetFixtureA()->GetBody();
		b2Shape::Type bodyType1 = contact->GetFixtureA()->GetShape()->m_type;
		b2Shape::Type bodyType2 = contact->GetFixtureB()->GetShape()->m_type;

		b2Body* b2 = contact->GetFixtureB()->GetBody();
		currentFloor = getCurrentFloor(b1);
		objSpeed = baseSpeed + (currentFloor / 1)*0.5;
		void* bodyAUserData = b1->GetUserData();
		void* bodyBUserData = b2->GetUserData();
		//check whether body1 is floorObject and body2 is PhoIngredient, weldJoint is not created
		if (bodyAUserData == bodyBUserData
			&& bodyType1 == 1 && bodyType2 == 2
			&& weldJointDef.userData == nullptr)
		{
			std::cout << "Cham" << std::endl;
			b1->SetLinearVelocity(b2Vec2(objSpeed - (rand() % 2) * objSpeed * 2, 0.0f));
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

	void Physics::EndContact(b2Contact* contact)
	{
		weldJointDef.userData = nullptr;
	}

	void Physics::Update(b2World* m_world)
	{

		static b2WeldJoint* weldJoint = nullptr;
		if (weldJointDef.bodyA != nullptr)
		{
			if (weldJointDef.userData == "canTao")
			{
				weldJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
				weldJointDef.userData = "daTao";
				weldJointDef.bodyA = nullptr;
				m_needMoveFloor = true;
			}
		}
		else if (m_button && weldJoint != nullptr && objBody->m_body->GetLinearVelocity().y == 0)
		{
			m_world->DestroyJoint(weldJoint);
			weldJoint = nullptr;
			float impulse = objBody->m_body->GetMass() * 0.2;
			objBody->m_body->ApplyLinearImpulse(b2Vec2(-2.1*objBody->m_body->GetLinearVelocity().x, 105), objBody->m_body->GetWorldCenter(), true);
			std::cout << "currentFloor: " << currentFloor << std::endl;

			m_button = false;
		}

		else if (m_needMoveFloor && objBody->m_body->GetLinearVelocity().y == 0 && currentFloor > 0)
		{

			int floorToBeRemoved = currentFloor - 2;
			int floorToBeUpdated = currentFloor + 3;
			if (currentFloor == 1)
			{
				floorObj[(currentFloor - 1) % 5]->m_body->SetActive(false);

			}
			else
			{
				floorObj[floorToBeRemoved % 5]->m_platform->SetTransform(b2Vec2(0, m_floorHeight*(floorToBeUpdated)), 0);
				floorObj[floorToBeRemoved % 5]->m_leftboundary->SetTransform(b2Vec2(0, m_floorHeight *(floorToBeUpdated)), 0);
				floorObj[floorToBeRemoved % 5]->m_rightboundary->SetTransform(b2Vec2(0, m_floorHeight *(floorToBeUpdated)), 0);
				floorObj[floorToBeRemoved % 5]->m_body->SetTransform(b2Vec2(RandomFloat(-m_floorWidth / 2 + 4, m_floorWidth / 2 - 4), m_floorHeight*(currentFloor + 3) + 0.5 + floorObj[0]->m_objLength), 0);
				floorObj[floorToBeRemoved % 5]->m_iobjLevel = floorToBeUpdated;
				floorObj[floorToBeRemoved % 5]->m_body->SetAwake(false);
				floorObj[floorToBeRemoved % 5]->m_body->SetActive(true);
				floorObj[(currentFloor - 1) % 5]->m_body->SetActive(false);
				//floorObj[(floorToBeRemoved+1) % 6]->m_body->SetActive(false);
			}
			m_needMoveFloor = false;

		}
		if (objBody->m_body->GetLinearVelocity().y > 0)
		{
			b2Fixture* fixture = floorObj[(currentFloor + 1) % 5]->m_body->GetFixtureList();
			b2Filter filter = fixture->GetFilterData();
			filter.groupIndex = k_largeGroup;
			fixture->SetFilterData(filter);
		}
		else if (objBody->m_body->GetLinearVelocity().y <= 0)
		{
			b2Fixture* fixture = floorObj[(currentFloor + 1) % 5]->m_body->GetFixtureList();
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
			}
			else if (floorObj[i]->m_body->GetPosition().x > m_floorWidth / 2 - 2)
			{
				vel.x = -objSpeed;
			}
			floorObj[i]->m_body->SetLinearVelocity(vel);
		}

	}

