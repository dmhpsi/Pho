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
#include "Testbed\Framework\Test.h"
#include "Testbed\Tests\MobileBalanced.h"

#include <iostream>
class MyContactListener : public b2ContactListener
{

public:

	void handleContact(b2Body* b1, b2Body* b2) 
	{
		b2Vec2 worldCoordsAnchorPoint = b2->GetWorldPoint(b2Vec2(0.6f, 0));
		b2WeldJointDef weldJointDef;
		weldJointDef.bodyA = b1;
		weldJointDef.bodyB = b2;
		weldJointDef.localAnchorA = weldJointDef.bodyA->GetLocalPoint(worldCoordsAnchorPoint);
		weldJointDef.localAnchorB = weldJointDef.bodyB->GetLocalPoint(worldCoordsAnchorPoint);
		weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
		//Test::m_world->CreateJoint(&weldJointDef);
		//b2Vec2 b1Pos = b2->GetPosition();
		//b1->SetTransform(b2->GetPosition(),0);
		//b2->SetTransform(b1->GetPosition(), 10);
		/*b2WeldJointDef weldJointDef;
		weldJointDef.bodyA = b1;
		weldJointDef.bodyB = b2;
		weldJointDef.type = b2JointType b2WeldJoint;
		weldJointDef.collideConnected = true;
		weldJointDef.localAnchorA.set(1, 0);
		weldJointDef.localAnchorB.set(-2, 0);
		world.createJoint(weldJointDef);*/
		//b1->SetTransform(b2->GetPosition(),0);
		//b2->SetTransform(b1->GetPosition(), 0);
	}
	void BeginContact(b2Contact* contact) {
		void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyAUserData!=NULL && bodyBUserData != NULL)
		{
			handleContact(contact->GetFixtureA()->GetBody(),
				contact->GetFixtureB()->GetBody());
			std::cout << "aaa";
		}

	}

};