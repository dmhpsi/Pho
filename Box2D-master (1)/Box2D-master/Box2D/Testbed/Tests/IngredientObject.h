#pragma once

#include "Testbed\Framework\Test.h"
class IngredientObject
{
public:
	b2Body* m_body;

public:
	IngredientObject(b2World* world) {
		m_body = NULL;
		b2BodyDef ingredientBodyDef;
		ingredientBodyDef.type = b2_dynamicBody;
		ingredientBodyDef.position.Set(-6.0f, 4.0f);
		m_body = world->CreateBody(&ingredientBodyDef);
		b2PolygonShape polyShape;
		b2FixtureDef ingredientFixtureDef;
		ingredientFixtureDef.filter.groupIndex = k_largeGroup;
		ingredientFixtureDef.density = 0.6f;
		ingredientFixtureDef.shape = &polyShape;
		polyShape.SetAsBox(1.0f, 1.0f);
		m_body->CreateFixture(&ingredientFixtureDef);

	}
	~IngredientObject() {}

};