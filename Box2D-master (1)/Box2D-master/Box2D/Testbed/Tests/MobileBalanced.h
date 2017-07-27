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

#pragma once
#include "vector"
#include "FloorObject.h"
#include "IngredientObject.h"
#include <iostream>


//
//const uint16 k_defaultCategory = 0x0001;
//const uint16 k_triangleCategory = 0x0002;
//const uint16 k_boxCategory = 0x0004;
//const uint16 k_circleCategory = 0x0008;
//
//const uint16 k_triangleMask = 0xFFFF;
//const uint16 k_boxMask = 0xFFFF ^ k_triangleCategory;
//const uint16 k_circleMask = 0xFFFF;

class MobileBalanced : public Test
{
public:
	b2WeldJointDef weldJointDef;
	int numOfFloor = 3;
	float floorWidth = 20.0f;
	float floorHeight = 17.5f;
	const int16	k_smallGroup = 1;
	const int16 k_largeGroup = -1;
	b2Fixture* m_platform;
	b2BodyDef bodyDef;
	std::vector<FloorObject*> floorObj;
	IngredientObject* objBody = new IngredientObject(m_world);
	bool m_button;

	MobileBalanced()
	{
		b2Vec2 deltaY(0.0f,floorHeight);
		b2Vec2 y(0.0f, floorHeight+0.5f);
		//Create boundary
		{
			b2Body* ground = m_world->CreateBody(&bodyDef);
			b2EdgeShape shape;
			//bottom bounadry
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
			ground->CreateFixture(&shape, 0.0f);

		}
		//Create object for each floor
		for (int i = 0; i < numOfFloor+1; i++)
		{
			FloorObject* obj = new FloorObject(m_world, i);
			obj->m_body->SetUserData(this);
			floorObj.push_back(obj);
		}
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
		//Create PHO INGREDIENT
		{
			objBody->m_body->SetUserData(this);

		}
		m_button = false;
		
	}
	void update(float dt)
	{
		//m_world.Step(dt, 6, 2);

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

	}
	void Step(Settings* settings)
	{
		static b2WeldJoint* weldJoint;
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


