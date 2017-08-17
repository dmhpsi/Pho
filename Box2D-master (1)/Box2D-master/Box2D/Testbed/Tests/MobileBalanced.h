#pragma once
#include "vector"
#include "FloorObject.h"
#include "IngredientObject.h"
#include <iostream>



class MobileBalanced : public Test
{
public:
	b2WeldJointDef weldJointDef;

	int m_inumOfFloor = 7;
	float m_floorWidth = 40.0f;
	float m_floorHeight = 17.5f;
	const int16 k_smallGroup = 1;
	int currentFloor;
	const float baseSpeed = 15.0f;
	float objSpeed = baseSpeed;
	const int16 k_largeGroup = -1;
	b2Fixture* m_platform;
	b2BodyDef bodyDef;
	std::vector<FloorObject*> floorObj;
	IngredientObject* objBody = new IngredientObject(m_world);
	bool m_button;
	bool m_needMoveFloor;
	MobileBalanced()
	{
		//Create object for each floor
		for (int i = 0; i < 6; i++)
		{
			FloorObject* obj = new FloorObject(m_world, i);
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
	void Keyboard(int key)
	{
		std::cout << "GLFW_KEY_A" << std::endl;
		switch (key)
		{
		case GLFW_KEY_A:
			//std::cout << "GLFW_KEY_A" << std::endl;
			m_button = true;
			break;
		case GLFW_KEY_E:
			std::cout << "--------------------" << std::endl;
			std::cout << currentFloor << std::endl;
			break;
		}
	}
	static Test* Create()
	{
		return new MobileBalanced;
	}

	int getCurrentFloor(b2Body* b1)
	{
		for (int i = 0; i < floorObj.size(); i++)
		{
			if (b1 == floorObj[i]->m_body)
			{
				return floorObj[i]->m_iobjLevel;
			}
		}
	}

	void BeginContact(b2Contact* contact)
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

	void EndContact(b2Contact* contact)
	{
		weldJointDef.userData = nullptr;
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
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
			m_button = false;
		}

		else if (m_needMoveFloor && objBody->m_body->GetLinearVelocity().y == 0 && currentFloor > 0)
		{

			int floorToBeRemoved = currentFloor - 3;
			int floorToBeUpdated = currentFloor + 3;
			if (currentFloor >2 && currentFloor <= m_inumOfFloor - 3)
			{
				floorObj[floorToBeRemoved % 6]->m_platform->SetTransform(b2Vec2(0, m_floorHeight*(floorToBeUpdated)), 0);
				floorObj[floorToBeRemoved % 6]->m_body->SetTransform(b2Vec2(RandomFloat(-m_floorWidth / 2 + 4, m_floorWidth / 2 - 4), m_floorHeight*(currentFloor + 3) + 0.5 + floorObj[0]->m_objLength), 0);
				floorObj[floorToBeRemoved % 6]->m_iobjLevel = floorToBeUpdated;
				floorObj[floorToBeRemoved % 6]->m_body->SetAwake(false);
				floorObj[floorToBeRemoved % 6]->m_body->SetActive(true);
				floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);
				//floorObj[(floorToBeRemoved+1) % 6]->m_body->SetActive(false);
			}
			else
			{
				floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);
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
			}
			else if (floorObj[i]->m_body->GetPosition().x > m_floorWidth / 2 - 2)
			{
				vel.x = -objSpeed;
			}
			floorObj[i]->m_body->SetLinearVelocity(vel);
		}
		g_debugDraw.DrawString(5, m_textLine, "Score: &d");
		m_textLine += DRAW_STRING_NEW_LINE;

	}

};