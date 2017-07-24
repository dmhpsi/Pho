#include "Box2D/Box2D.h"
#include "Play.h"

#include <stdio.h>

b2Vec2 gravity(0.0f, -10.0f);
b2World world(gravity); 

void Play::Playgame() 
{
	b2BodyDef bodyDef;
	
	bodyDef.position.Set(160, 120);
	bodyDef.type = b2_staticBody;
	b2Body* body = world.CreateBody(&bodyDef); 
	b2PolygonShape shape;
	shape.SetAsBox(50, 5);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
}

void Play::update(float dt)
{
	world.Step(dt, 6, 2);
}
