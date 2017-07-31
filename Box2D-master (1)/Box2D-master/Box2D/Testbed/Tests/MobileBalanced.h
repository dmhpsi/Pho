#pragma once
#include "vector"
#include "FloorObject.h"
#include "IngredientObject.h"
#include <iostream>



class MobileBalanced : public Test
{
public:
	b2WeldJointDef weldJointDef;

	int m_inumOfFloor = 10;
	float m_floorWidth = 40.0f;
	float m_floorHeight = 17.5f;
	const int16 k_smallGroup = 1;
	int currentFloor;
	float objSpeed = 15.0f;
	const int16 k_largeGroup = -1;
	b2Fixture* m_platform;
	b2BodyDef bodyDef;
	std::vector<FloorObject*> floorObj;
	IngredientObject* objBody = new IngredientObject(m_world);
	bool m_button;

	MobileBalanced()
	{
		//Create boundary
		{
			b2Body* ground = m_world->CreateBody(&bodyDef);
			b2EdgeShape shape;
			//bottom bounadry
			shape.Set(b2Vec2(-m_floorWidth / 2, 0.0f), b2Vec2(m_floorWidth / 2, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
			//top bounadry
			//shape.Set(b2Vec2(-m_floorWidth / 2, m_floorHeight*m_inumOfFloor + m_floorHeight), b2Vec2(m_floorWidth / 2, m_floorHeight*m_inumOfFloor + m_floorHeight));
			//ground->CreateFixture(&shape, 0.0f);
			//left bounadry
			shape.Set(b2Vec2(-m_floorWidth / 2, 0.0f), b2Vec2(-m_floorWidth / 2, m_floorHeight*m_inumOfFloor + m_floorHeight));
			ground->CreateFixture(&shape, 0.0f);
			//right bounadry
			shape.Set(b2Vec2(m_floorWidth / 2, 0.0f), b2Vec2(m_floorWidth / 2, m_floorHeight*m_inumOfFloor + m_floorHeight));
			ground->CreateFixture(&shape, 0.0f);

		}
		//Create object for each floor
		for (int i = 0; i < 5; i++)
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

	}
	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			m_button = true;
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


		objSpeed += currentFloor * 0.5;
		void* bodyAUserData = b1->GetUserData();
		void* bodyBUserData = b2->GetUserData();
		if (bodyAUserData == bodyBUserData && bodyType1 == 1 && bodyType2 == 2 && weldJointDef.userData == NULL)
		{
			b1->SetLinearVelocity(b2Vec2(objSpeed - (rand() % 2) * objSpeed *2, 0.0f));
			b2Vec2 worldCoordsAnchorPoint = b2->GetWorldPoint(b2Vec2(0.6f, 0));
			weldJointDef.bodyA = b1;
			weldJointDef.bodyB = b2;
			b2Vec2 edgePos = weldJointDef.bodyB->GetLocalPoint(worldCoordsAnchorPoint);
			weldJointDef.localAnchorB = edgePos;
			edgePos.y += 2.5f;
			weldJointDef.localAnchorA = edgePos;
			weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
			weldJointDef.userData = "notcreated";
		}
		else
		{
			weldJointDef.userData == NULL;
		}
	}
	void EndContact(b2Contact* contact)
	{

		weldJointDef.userData = NULL;
	}
	void Step(Settings* settings)
	{
		static b2WeldJoint* weldJoint;

		if (weldJointDef.bodyA != nullptr )
		{
			if (weldJointDef.userData == "notcreated")
			{
				weldJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
				weldJointDef.userData = "created";

			}
		}
		if (m_button && weldJoint != nullptr && objBody->m_body->GetLinearVelocity().y == 0)
		{
			weldJoint->GetBodyA()->SetActive(false);
			m_world->DestroyJoint(weldJoint);
			weldJointDef.userData = NULL;
			weldJoint = NULL;
			float impulse = objBody->m_body->GetMass() * 0.2;
			objBody->m_body->ApplyLinearImpulse(b2Vec2(-2.1*objBody->m_body->GetLinearVelocity().x, 105), objBody->m_body->GetWorldCenter(), true);
			
			//if (currentFloor>0 && currentFloor<m_inumOfFloor-3)
			if (currentFloor>0)
			{ 
				FloorObject* obj = new FloorObject(m_world, currentFloor + 4);
				obj->m_body->SetUserData(this);
				floorObj.push_back(obj);
			}
			/*float magnitude = 100;
			b2Vec2 forceDirection = objBody->m_body->GetWorldVector(b2Vec2(0, 1));

			forceDirection = magnitude * forceDirection;
			objBody->m_body->ApplyLinearImpulse(forceDirection, objBody->m_body->GetPosition(), true);*/
			m_button = false;
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
		Test::Step(settings);
		g_debugDraw.DrawString(5, m_textLine, "Press 'a' to control the flippers");
		m_textLine += DRAW_STRING_NEW_LINE;

	}

};