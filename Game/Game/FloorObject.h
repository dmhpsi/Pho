#pragma once
#include "Box2D/Box2D.h"
#include "define.h"


class FloorObject
{
public:

	b2Body* m_body;
	b2Body* m_platform;
	b2Body* m_leftboundary;
	b2Body* m_rightboundary;
	int m_iobjLevel;
	float m_objLength = 1.5f;
public:
	FloorObject(b2World* world, int objLevel) {
		{
			m_iobjLevel = objLevel;
			b2BodyDef bodyDef;
			bodyDef.position = b2Vec2(0.0f, m_floorHeight*objLevel);
			bodyDef.type = b2_staticBody;
			m_platform = world->CreateBody(&bodyDef);
			b2FixtureDef boxShape;
			b2PolygonShape shape;
			shape.SetAsBox(m_floorWidth / 2, 0.5f);
			boxShape.shape = &shape;
			boxShape.filter.groupIndex = k_largeGroup;
			m_platform->CreateFixture(&boxShape);
		}
		{
			b2FixtureDef myFixtureDef2;
			b2FixtureDef myFixtureDef;

			//fixture for the polyshape
			b2Fixture* m_piece1;
			//fixture for the edgeshape
			b2Fixture* m_piece2;
			b2Vec2 x = b2Vec2(RandomFloat(-m_floorWidth / 2 + 4, m_floorWidth / 2 - 4), m_objLength + 0.5 + m_floorHeight*objLevel);
			if (objLevel == 0)
			{
				x.x = -6.0f;
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
			myFixtureDef2.filter.groupIndex = k_smallGroup;
			myFixtureDef2.shape = &edgeShape;
			m_piece1 = m_body->CreateFixture(&myFixtureDef2);
		}
		{
			b2BodyDef bodyDef1;
			bodyDef1.position = b2Vec2(0.0f, m_floorHeight*objLevel);
			b2BodyDef bodyDef2;

			bodyDef2.position = b2Vec2(0.0f, m_floorHeight*objLevel);

			m_leftboundary = world->CreateBody(&bodyDef1);
			m_rightboundary = world->CreateBody(&bodyDef2);
			b2EdgeShape shape;
			//update left and right boundary based on the current floor
			shape.Set(b2Vec2(-m_floorWidth / 2, 0.0f),
				b2Vec2(-m_floorWidth / 2, m_floorHeight));

			m_leftboundary->CreateFixture(&shape, 0.0f);

			shape.Set(b2Vec2(m_floorWidth / 2, 0.0f),
				b2Vec2(m_floorWidth / 2, m_floorHeight));
			m_rightboundary->CreateFixture(&shape, 0.0f);
		}

	}

	~FloorObject()
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}

};