<<<<<<< HEAD
=======
/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

>>>>>>> dmhpsi/huynx
#pragma once
#include "vector"
#include "FloorObject.h"
#include "IngredientObject.h"
#include <iostream>


<<<<<<< HEAD
=======
//
//const uint16 k_defaultCategory = 0x0001;
//const uint16 k_triangleCategory = 0x0002;
//const uint16 k_boxCategory = 0x0004;
//const uint16 k_circleCategory = 0x0008;
//
//const uint16 k_triangleMask = 0xFFFF;
//const uint16 k_boxMask = 0xFFFF ^ k_triangleCategory;
//const uint16 k_circleMask = 0xFFFF;
>>>>>>> dmhpsi/huynx

class MobileBalanced : public Test
{
public:
	b2WeldJointDef weldJointDef;
<<<<<<< HEAD

	int m_inumOfFloor = 10;
	float m_floorWidth = 40.0f;
	float m_floorHeight = 17.5f;
	const int16 k_smallGroup = 1;
	int currentFloor;
	float objSpeed = 15.0f;
=======
	int numOfFloor = 3;
	float floorWidth = 20.0f;
	float floorHeight = 17.5f;
	const int16	k_smallGroup = 1;
>>>>>>> dmhpsi/huynx
	const int16 k_largeGroup = -1;
	b2Fixture* m_platform;
	b2BodyDef bodyDef;
	std::vector<FloorObject*> floorObj;
	IngredientObject* objBody = new IngredientObject(m_world);
	bool m_button;

	MobileBalanced()
	{
<<<<<<< HEAD
=======
		b2Vec2 deltaY(0.0f,floorHeight);
		b2Vec2 y(0.0f, floorHeight+0.5f);
>>>>>>> dmhpsi/huynx
		//Create boundary
		{
			b2Body* ground = m_world->CreateBody(&bodyDef);
			b2EdgeShape shape;
			//bottom bounadry
<<<<<<< HEAD
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
=======
			shape.Set(b2Vec2(-floorWidth, 0.0f), b2Vec2(floorWidth, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
			//top bounadry
			shape.Set(b2Vec2(-floorWidth, floorHeight*numOfFloor+ floorHeight), b2Vec2(floorWidth, floorHeight*numOfFloor + floorHeight));
			ground->CreateFixture(&shape, 0.0f);
			//left bounadry
			shape.Set(b2Vec2(-floorWidth, 0.0f), b2Vec2(-floorWidth, floorHeight*numOfFloor + floorHeight));
			ground->CreateFixture(&shape, 0.0f);
			//right bounadry
			shape.Set(b2Vec2(floorWidth, 0.0f), b2Vec2(floorWidth, floorHeight*numOfFloor + floorHeight));
>>>>>>> dmhpsi/huynx
			ground->CreateFixture(&shape, 0.0f);

		}
		//Create object for each floor
<<<<<<< HEAD
		for (int i = 0; i < 5; i++)
=======
		for (int i = 0; i < numOfFloor+1; i++)
>>>>>>> dmhpsi/huynx
		{
			FloorObject* obj = new FloorObject(m_world, i);
			obj->m_body->SetUserData(this);
			floorObj.push_back(obj);
		}
<<<<<<< HEAD

=======
		//Create platform for each floor
		for(float i=0.0f ; i<numOfFloor; i++)
		{
			bodyDef.position = y;
			bodyDef.type = b2_staticBody;
			b2Body* body = m_world->CreateBody(&bodyDef);
			b2FixtureDef boxShape;
			b2PolygonShape shape;
			shape.SetAsBox(20.0f, 0.5f);
			boxShape.shape = &shape;
			boxShape.filter.groupIndex = k_largeGroup;
			//body->CreateFixture(&shape, 0.0f);
			body->CreateFixture(&boxShape);
			y += deltaY;

		}
>>>>>>> dmhpsi/huynx
		//Create PHO INGREDIENT
		{
			objBody->m_body->SetUserData(this);

		}
<<<<<<< HEAD

		m_button = false;
=======
		m_button = false;
		
	}
	void update(float dt)
	{
		//m_world.Step(dt, 6, 2);
>>>>>>> dmhpsi/huynx

	}
	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_A:
			m_button = true;
<<<<<<< HEAD
			break;
=======
		break;
>>>>>>> dmhpsi/huynx
		}
	}
	static Test* Create()
	{
		return new MobileBalanced;
	}
<<<<<<< HEAD

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
=======
	void BeginContact(b2Contact* contact)
	{
		b2Body* b1 = contact->GetFixtureA()->GetBody();
		b2Body* b2 = contact->GetFixtureB()->GetBody();
		void* bodyAUserData = b1->GetUserData();
		void* bodyBUserData = b2->GetUserData();
		if (bodyAUserData == bodyBUserData )
		{
			b2Vec2 worldCoordsAnchorPoint = b2->GetWorldPoint(b2Vec2(0.6f, 0));
			weldJointDef.bodyA = b1;
			weldJointDef.bodyB = b2;
			weldJointDef.localAnchorA = weldJointDef.bodyA->GetLocalPoint(worldCoordsAnchorPoint);
			weldJointDef.localAnchorB = weldJointDef.localAnchorA + b2Vec2(0, 2.5f);
			weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
			//m_button = true;
			std::cout << "cac";
			weldJointDef.userData = NULL;

		}

>>>>>>> dmhpsi/huynx
	}
	void Step(Settings* settings)
	{
		static b2WeldJoint* weldJoint;
<<<<<<< HEAD

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
=======
		if (weldJointDef.bodyA != nullptr)
		{ 
			if (weldJointDef.userData == NULL)
			{
				weldJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
				weldJointDef.userData = "a";
			}
		}
		if (m_button && weldJoint != nullptr)
		{
			m_world->DestroyJoint(weldJoint);
			weldJoint = NULL;
			float impulse = objBody->m_body->GetMass() * 0.2;
			objBody->m_body->ApplyLinearImpulse(b2Vec2(0, 20), objBody->m_body->GetWorldCenter(), true);
			m_button = false;

		}
		for(int i=0;i<floorObj.size();i++)
		{
			b2Vec2 vel = floorObj[i]->m_body->GetLinearVelocity();
			if (floorObj[i]->m_body->GetPosition().x < -18.0f)
			{
				vel.x = 20;
			}
			else if (floorObj[i]->m_body->GetPosition().x > 18.0f)
			{
				vel.x = -20;
			}
			floorObj[i]->m_body->SetLinearVelocity(vel);
		}

		Test::Step(settings);

		g_debugDraw.DrawString(5, m_textLine, "Press 'a' to control the flippers");
		m_textLine += DRAW_STRING_NEW_LINE;
		
	}

};


>>>>>>> dmhpsi/huynx
