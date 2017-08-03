#include "stdafx.h"
#include "PhysicManager.h"
//#include "Physics.h"
#include <stdio.h>


//Physics myContactListenerInstance;

PhysicManager* PhysicManager::Instance = 0;
PhysicManager::PhysicManager()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -40.0f);
	m_world = new b2World(gravity);
	//m_world->SetContactListener(&myContactListenerInstance);
	b2BodyDef bodyDef;
	m_groundBody = m_world->CreateBody(&bodyDef);
}
PhysicManager* PhysicManager::GetInstance()
{
	if (!Instance)
	{
		Instance = new PhysicManager();
	}
	return Instance;
}

void PhysicManager::Update()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		m_world->Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		//b2Vec2 position = body->GetPosition();
		//float32 angle = body->GetAngle();
	}

}

void PhysicManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}
PhysicManager::~PhysicManager()
{

}