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

class MobileBalanced : public Test
{
public:
	int numOfFloor = 10;
	enum _entityCategory {
		BOUNDARY = 0x0001,
		GEM = 0x0002,
		WORKER = 0x0004,
	};
	enum State
	{
		e_unknown,
		e_above,
		e_below
	};
	int32 remainingJumpSteps;
	float32 m_radius, m_top, m_bottom;
	State m_state;
	b2Fixture* m_platform;
	//b2Body* body2[10];
	b2Fixture* m_character;
	b2BodyDef bd;
	b2Body* objBody;
	std::vector<b2Body*> floorObj;

	bool m_button;
	MobileBalanced()
	{

		b2Vec2 deltaY(0.0f,10.0f);
		b2Vec2 y(0.0f, 10.5f);
		b2Vec2 gravity(0.0f, -10.0f);
		m_world->SetGravity(gravity);
		//Create object in 1st floor
		{
			b2BodyDef bodyDef;
			bodyDef.position.Set(0.0f, 0.5f);
			bodyDef.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);
			m_platform = body->CreateFixture(&shape, 0.0f);
		}
		//Create boundary
		{
			b2Body* ground = m_world->CreateBody(&bd);
			b2EdgeShape shape;
			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
			shape.Set(b2Vec2(-20.0f, 10.0f*numOfFloor+10.0f), b2Vec2(20.0f, 10.0f*numOfFloor + 10.0f));
			ground->CreateFixture(&shape, 0.0f);
			shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(-20.0f, 10.0f*numOfFloor + 10.0f));
			ground->CreateFixture(&shape, 0.0f);
			shape.Set(b2Vec2(20.0f, 0.0f), b2Vec2(20.0f, 10.0f*numOfFloor + 10.0f));
			ground->CreateFixture(&shape, 0.0f);
		}
		//Create object for each floor
		for (int i = 0.0f; i < numOfFloor; i++)
		{
			b2Vec2 x = b2Vec2(RandomFloat(-19.0f, 19.0f), 10.5f + 10.0f*i);
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position = x;
			b2PolygonShape shape;
			b2Body *body2 = m_world->CreateBody(&bodyDef);
			shape.SetAsBox(0.5f,0.5f);
			body2->CreateFixture(&shape, 0.0f);
			body2->SetLinearVelocity(b2Vec2(20-(rand()%2)*40, 0.0f));
			floorObj.push_back(body2);
		}
		//Create platform for each floor
		for(float i=0.0f ; i<numOfFloor; i++)
		{
			bd.position = y;
			b2Body* body = m_world->CreateBody(&bd);
			b2PolygonShape shape;
			shape.SetAsBox(20.0f, 0.5f);
			body->CreateFixture(&shape, 0.0f);
			y += deltaY;
		}
		//Create PHO INGREDIENT
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, 1.5f);
			objBody = m_world->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);
			objBody->CreateFixture(&shape, 0.0f);
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
	void Step(Settings* settings)
	{

		if (m_button)
		{

		}
		for(int i=0;i<floorObj.size();i++)
		{
			b2Vec2 vel = floorObj[i]->GetLinearVelocity();
			if (floorObj[i]->GetPosition().x < -19.0f)
			{
			vel.x = 20;
			}
			else if (floorObj[i]->GetPosition().x > 19.0f)
			{
			vel.x = -20;
			}
			floorObj[i]->SetLinearVelocity(vel);
		}

		Test::Step(settings);

		g_debugDraw.DrawString(5, m_textLine, "Press 'a' to control the flippers");
		m_textLine += DRAW_STRING_NEW_LINE;

	}

};


