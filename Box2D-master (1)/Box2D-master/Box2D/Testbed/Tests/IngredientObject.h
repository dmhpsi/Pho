#pragma once

#include "Testbed\Framework\Test.h"
class IngredientObject
{
public:
	b2Body* m_body;

public:
	IngredientObject(b2World* world) {
		m_body = NULL;
		//set up dynamic body, store in class variable
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position.Set(-6.0f, 4.0f);
		m_body = world->CreateBody(&myBodyDef);
		//add circle fixture
		b2PolygonShape polyShape;
		b2FixtureDef myFixtureDef;
		myFixtureDef.filter.groupIndex = k_largeGroup;
		
		myFixtureDef.shape = &polyShape;
		polyShape.SetAsBox(1.0f, 1.0f);
		//m_body->CreateFixture(&polyShape, 0.0f);
		m_body->CreateFixture(&myFixtureDef);

	}
	~IngredientObject() {}

};
