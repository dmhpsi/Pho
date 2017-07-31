<<<<<<< HEAD
#pragma once
#include "Testbed\Framework\Test.h"
#include "MobileBalanced.h"

float m_floorHeight = 17.5f;
float m_floorWidth = 40.0f;

class FloorObject
{
public:

	b2Body* m_body;
	int m_iobjLevel;
	float m_objLength = 1.5f;
public:
	FloorObject(b2World* world, int i) {
		{
			m_iobjLevel = i;
			b2BodyDef bodyDef;
			if (i != 0)
			{
				bodyDef.position = b2Vec2(0.0f, 0.5f + m_floorHeight*i);
				bodyDef.type = b2_staticBody;
				b2Body* body = world->CreateBody(&bodyDef);
				b2FixtureDef boxShape;
				b2PolygonShape shape;
				shape.SetAsBox(m_floorWidth / 2, 0.5f);
				boxShape.shape = &shape;
				boxShape.filter.groupIndex = k_largeGroup;
				body->CreateFixture(&boxShape);
			}
		}
		{
			b2FixtureDef myFixtureDef;
			//fixture for the polyshape
			b2Fixture* m_piece1;
			//fixture for the edgeshape
			b2Fixture* m_piece2;
			b2Vec2 x = b2Vec2(RandomFloat(-m_floorWidth / 2 + 2, m_floorWidth / 2 - 2), m_objLength + 1.1 + m_floorHeight*i);
			if (i == 0)
			{
				x.x = -6.0f; x.y = m_objLength;
			}
			b2BodyDef bd;
			bd.type = b2_kinematicBody;
			bd.position = x;
			m_body = world->CreateBody(&bd);
			//m_body->SetLinearVelocity(b2Vec2(20 - (rand() % 2) * 40, 0.0f));
			m_body->SetGravityScale(0);
			b2PolygonShape polyShape;
			polyShape.SetAsBox(m_objLength, m_objLength);
			myFixtureDef.filter.groupIndex = k_largeGroup;
			myFixtureDef.shape = &polyShape;
			m_piece1 = m_body->CreateFixture(&myFixtureDef);
			b2EdgeShape edgeShape;
			edgeShape.Set(b2Vec2(-m_objLength, m_objLength), b2Vec2(m_objLength, m_objLength));
			m_piece2 = m_body->CreateFixture(&edgeShape, 1.0f);
		}

	}

	~FloorObject() 
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}

};
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

#pragma once
#include "Testbed\Framework\Test.h"
float floorHeight = 17.5f;
class FloorObject
{
public:
	b2Body* m_body;

public:
	FloorObject(b2World* world, int i) {
		m_body = NULL;
		b2Vec2 x = b2Vec2(RandomFloat(-19.0f, 19.0f), 2.5f + floorHeight*i);
		if (i == 0)
		{
			x.x = -6.0f; x.y = 1.5f;
		}
		//set up dynamic body, store in class variable
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_kinematicBody;
		myBodyDef.position = x;
		m_body = world->CreateBody(&myBodyDef);
		//add circle fixture
		b2PolygonShape polyShape;
		b2FixtureDef myFixtureDef;
		//if (i == 0) startingpoint = x.x;
		polyShape.SetAsBox(1.5f, 1.5f);
		m_body->CreateFixture(&polyShape, 0.0f);
		m_body->SetLinearVelocity(b2Vec2(20 - (rand() % 2) * 40, 0.0f));
		m_body->SetGravityScale(0);
	}
	~FloorObject() {}

};

>>>>>>> dmhpsi/huynx
