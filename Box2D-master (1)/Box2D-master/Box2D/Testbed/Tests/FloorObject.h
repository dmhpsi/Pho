#pragma once
#include "Testbed\Framework\Test.h"
#include "MobileBalanced.h"

float floorHeight = 17.5f;
float floorWidth = 40.0f;

class FloorObject
{
public:
	b2Body* m_body;
	float m_objLength = 1.5f;
public:
	FloorObject(b2World* world, int i) {
		m_body = NULL;
		b2FixtureDef myFixtureDef;
		//fixture for the polyshape
		b2Fixture* m_piece1;
		//fixture for the edgeshape
		b2Fixture* m_piece2;
		b2Vec2 x = b2Vec2(RandomFloat(-floorWidth / 2 + 2, floorWidth / 2 - 2), m_objLength + 1 + floorHeight*i);
		if (i == 0)
		{
			x.x = -6.0f; x.y = m_objLength;
		}
		b2BodyDef bd;
		bd.type = b2_kinematicBody;
		bd.position = x;
		m_body = world->CreateBody(&bd);
		m_body->SetLinearVelocity(b2Vec2(20 - (rand() % 2) * 40, 0.0f));
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
	~FloorObject() {}

};