#include "stdafx.h"
#include "PhysicManager.h"

PhysicManager* PhysicManager::Instance = 0;
PhysicManager::PhysicManager()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -40.0f);
	m_world = new b2World(gravity);
	m_world->SetContactListener(this);
	b2BodyDef bodyDef;
	m_groundBody = m_world->CreateBody(&bodyDef);
	objBody = NULL;
}
PhysicManager* PhysicManager::GetInstance()
{
	if (!Instance)
	{
		Instance = new PhysicManager();
	}
	return Instance;
}

void PhysicManager::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}
PhysicManager::~PhysicManager()
{
	for (int i = 0; i < floorObj.size(); i++)
	{
		delete floorObj[i];
	}
	if(m_inumOfFloor==0)delete lastFloor;
	if (objBody != NULL)
		delete objBody;
	delete m_world;
	m_world = NULL;
}

void PhysicManager::Init(const char* physicsFile)
{
	int numObject, objLevel, numOfLevels, levelID, numOfFloor, levelSpeed;
	int numPhysicBodies;
	int object[3];
	char link[30];
	endGame = false;
	winGame = false;
	FILE *Resource;

	numParticle = 1;
	listParticle = &SceneManager::GetInstance()->listObject[17];
	listParticle[0].SetVisible(true, 0); 

	fopen_s(&Resource, physicsFile, "r");
	fscanf_s(Resource, "#Levels: %d\n", &numOfLevels);
	for (int i = 0; i < numOfLevels; i++)
	{
		fscanf(Resource, "ID %d\n", &levelID);
		fscanf(Resource, "FLOORS %d\n", &numOfFloor);
		fscanf(Resource, "BASESPEED %d\n", &levelSpeed);
		if (m_ilevel == levelID)
		{
			baseSpeed = levelSpeed;
			m_inumOfFloor = numOfFloor;
		}
	}
	fscanf_s(Resource, "#PhysicBodies: %d\n", &numPhysicBodies);
	for (int i = 0; i < numPhysicBodies; i++)
	{
		fscanf(Resource, "ID %d\n", &objLevel);
		fscanf_s(Resource, "OBJECTS %d\n", &numObject);
		for (int i = 0; i < numObject; i++)
		{
			fscanf(Resource, "OBJECT %d\n", &object[i]);
		}
		fscanf(Resource, "TYPE %s\n", link);
		if (strcmp(link, "FLOOR_OBJ") == 0)
		{
			FloorObject* obj = new FloorObject(m_world, objLevel);
			obj->m_platform->SetUserData(&SceneManager::GetInstance()->listObject[object[0]]);
			obj->m_body->SetUserData(&SceneManager::GetInstance()->listObject[object[1]]);
			floorObj.push_back(obj);
		}
		else if (strcmp(link, "INGRE_OBJ") == 0)
		{
			objBody = new IngredientObject(m_world);
			objBody->m_body->SetUserData(&SceneManager::GetInstance()->listObject[object[0]]);
		}
		if (strcmp(link, "FINALFLOOR_OBJ") == 0)
		{
			if (m_inumOfFloor == 0)
			{
				lastFloor = new FloorObject(m_world, 1000);
				lastFloor->m_platform->SetUserData(&SceneManager::GetInstance()->listObject[object[0]]);
				lastFloor->m_body->SetUserData(&SceneManager::GetInstance()->listObject[object[1]]);
				lastFloor->m_body->SetTransform(b2Vec2(0, lastFloor->m_body->GetPosition().y), 0);
				((Object*)lastFloor->m_body->GetUserData())->SetVisible(true, 0);
				((Object*)lastFloor->m_platform->GetUserData())->SetVisible(true, 0);
			}
			else
			{
				lastFloor = new FloorObject(m_world, m_inumOfFloor);
				lastFloor->m_platform->SetUserData(&SceneManager::GetInstance()->listObject[object[0]]);
				lastFloor->m_body->SetUserData(&SceneManager::GetInstance()->listObject[object[1]]);
				lastFloor->m_body->SetTransform(b2Vec2(0, lastFloor->m_body->GetPosition().y), 0);
				floorObj.push_back(lastFloor);
			}
		}
	}

	SceneManager::GetInstance()->listObject[18].SetVisible(true, 0);

	m_button = false;
	m_needMoveFloor = false;
}

void PhysicManager::Keyboard(int key)
{
	if (key == VK_SPACE)
	{
		m_button = true;
	}
}

void PhysicManager::MouseClick()
{
	m_button = true;
}

int PhysicManager::getCurrentFloor(b2Body* b1)
{
	for (int i = 0; i < floorObj.size(); i++)
	{
		if (b1 == floorObj[i]->m_body)
		{
			return floorObj[i]->m_iobjLevel;
		}
	}
}

void PhysicManager::BeginContact(b2Contact* contact)
{
	if (objBody == NULL)
	{
		return;
	}
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Shape::Type bodyType1 = contact->GetFixtureA()->GetShape()->m_type;
	b2Shape::Type bodyType2 = contact->GetFixtureB()->GetShape()->m_type;

	b2Body* b2 = contact->GetFixtureB()->GetBody();
	currentFloor = getCurrentFloor(b1);
	objSpeed = baseSpeed + (currentFloor / 1)*0.5;
	void* bodyAUserData = b1->GetUserData();
	void* bodyBUserData = b2->GetUserData();
	int x = b1->GetType();
	int y = b2->GetType();
	//check whether body1 is floorObject and body2 is PhoIngredient, weldJoint is not created
	if (x == 1 && y == 2
		&& bodyType1 == 1 && bodyType2 == 2
		&& weldJointDef.userData == nullptr)
	{
		std::cout << "Cham" << std::endl;
		int x = objSpeed - (rand() % 2) * objSpeed * 2;
		b1->SetLinearVelocity(b2Vec2(x, 0.0f));
		if (x > 0)
		{
			((Object*)b1->GetUserData())->SetFlip(true);
		}
		else
		{
			((Object*)b1->GetUserData())->SetFlip(false);
		}
		b2Vec2 worldCoordsAnchorPoint = b2->GetWorldPoint(b2Vec2(0.6f, 0));
		weldJointDef.bodyA = b1;
		weldJointDef.bodyB = b2;
		b2Vec2 edgePos = weldJointDef.bodyB->GetLocalPoint(worldCoordsAnchorPoint);
		weldJointDef.localAnchorB = edgePos;
		edgePos.y += 2.51f;
		weldJointDef.localAnchorA = edgePos;
		weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
		weldJointDef.userData = "canTao";
	}
}

void PhysicManager::EndContact(b2Contact* contact)
{
	weldJointDef.userData = nullptr;
}

void PhysicManager::Update(float dt)
{
	//if (objBody == NULL)
	//{
	//	return;
	//}
	m_timeStep = dt;
	m_velocityIterations = 6;
	m_positionIterations = 2;
	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	static b2WeldJoint* weldJoint = nullptr;
	if (weldJointDef.bodyA != nullptr)
	{
		if (weldJointDef.userData == "canTao")
		{
			// Catch
			ResourceManager::GetInstance()->listSounds[3].Replay();
			weldJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
			weldJointDef.userData = "daTao";
			weldJointDef.bodyA = nullptr;
			m_needMoveFloor = true;
			if (currentFloor == m_inumOfFloor - 1 || currentFloor == m_inumOfFloor && m_inumOfFloor != 0)
			{
				Camera::GetInstance()->SetHeight(lastFloor->m_body->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth, 1000);
			}
			else
			{
				Camera::GetInstance()->SetHeight(floorObj[(currentFloor + 1) % 6]->m_body->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth, 1000);
			}
			((Object*)floorObj[(currentFloor) % 6]->m_body->GetUserData())->SetStatus(OBJ_RUN);
			//((Object*)objBody->m_body->GetUserData())->SetVisible(false, 100);
			if (currentFloor > 0)
			{
				listParticle[0].SetPosition(objBody->m_body->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth,
					objBody->m_body->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth);
				listParticle[0].SetVisible(true, 1080);
			}
		}
	}
	else if (m_button && weldJoint != nullptr && objBody->m_body->GetLinearVelocity().y == 0)
	{
		// Throw
		ResourceManager::GetInstance()->listSounds[2].Replay();
		m_world->DestroyJoint(weldJoint);
		weldJoint = nullptr;
		float impulse = objBody->m_body->GetMass() * 0.2;
		objBody->m_body->ApplyLinearImpulse(b2Vec2(-2.1*objBody->m_body->GetLinearVelocity().x, 105), objBody->m_body->GetWorldCenter(), true);
		std::cout << "currentFloor: " << currentFloor << std::endl;
		((Object*)floorObj[(currentFloor) % 6]->m_body->GetUserData())->SetStatus(OBJ_IDLE);
		m_button = false;
	}

	else if (m_needMoveFloor && objBody->m_body->GetLinearVelocity().y == 0 && currentFloor > 0)
	{
		int floorToBeRemoved = currentFloor - 3;
		int floorToBeUpdated = currentFloor + 3;
		if (currentFloor >2 && currentFloor < m_inumOfFloor - 3 || currentFloor >2 && m_inumOfFloor == 0)
		{
			floorObj[floorToBeRemoved % 6]->m_platform->SetTransform(b2Vec2(0, m_floorHeight*(floorToBeUpdated)), 0);
			floorObj[floorToBeRemoved % 6]->m_body->SetTransform(b2Vec2(RandomFloat(-m_floorWidth / 2 + 4, m_floorWidth / 2 - 4), m_floorHeight*(currentFloor + 3) + 0.5 + floorObj[0]->m_objLength), 0);
			floorObj[floorToBeRemoved % 6]->m_iobjLevel = floorToBeUpdated;
			if (currentFloor < 6)
			{
				floorObj[floorToBeRemoved % 6]->m_body->SetAwake(false);
				floorObj[floorToBeRemoved % 6]->m_body->SetActive(true);
			}
			else
			{
				floorObj[floorToBeRemoved % 6]->m_body->SetAwake(true);
				floorObj[floorToBeRemoved % 6]->m_body->SetActive(true);
				floorObj[floorToBeRemoved % 6]->m_body->SetLinearVelocity(b2Vec2(5,0));
			}
			floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);
		}
		else 
		{
			floorObj[(currentFloor - 1) % 6]->m_body->SetActive(false);
		}
		m_needMoveFloor = false;

	}

	if (objBody->m_body->GetLinearVelocity().y > 0)
	{
		b2Fixture* fixture = floorObj[(currentFloor + 1) % 6]->m_body->GetFixtureList();
		b2Filter filter = fixture->GetFilterData();
		filter.groupIndex = k_largeGroup;
		fixture->SetFilterData(filter);
	}
	else if (objBody->m_body->GetLinearVelocity().y <= -1)
	{
		b2Fixture* fixture = floorObj[(currentFloor + 1) % 6]->m_body->GetFixtureList();
		b2Filter filter = fixture->GetFilterData();
		filter.groupIndex = k_smallGroup;
		fixture->SetFilterData(filter);
		if (endGame)
			return;
		if (currentFloor == 0 && objBody->m_body->GetPosition().y < floorObj[currentFloor]->m_platform->GetPosition().y)
		{
			SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(false, 0);
			SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->loseTextureId].SetVisible(false, 0);
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].visibleSet == true)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].SetVisible(false, 0);
				StateMachine::GetInstance()->listButtons[B_REPLAY].SetProperty(319, 432, 94, 90, B_REPLAY);
			}
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].visibleSet == true)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(false, 0);
				StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 432, 94, 92, B_HOME);
			}
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].visibleSet == false)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].SetVisible(true, 0);
				StateMachine::GetInstance()->listButtons[B_RESUME].SetProperty(319, 432, 94, 90, B_VOID);
			}
			endGame = true;
		}
		else if (currentFloor > 0 && objBody->m_body->GetPosition().y < floorObj[(currentFloor-1) % 6]->m_platform->GetPosition().y )
		{
			SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(false, 0);
			SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->loseTextureId].SetVisible(false, 0);
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].visibleSet == true)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].SetVisible(false, 0);
				StateMachine::GetInstance()->listButtons[B_REPLAY].SetProperty(319, 432, 94, 90, B_REPLAY);
			}
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].visibleSet == true)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(false, 0);
				StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 432, 94, 92, B_HOME);
			}
			if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].visibleSet == false)
			{
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->resumeButtonId].SetVisible(true, 0);
				StateMachine::GetInstance()->listButtons[B_RESUME].SetProperty(319, 432, 94, 90, B_VOID);
			}
			endGame = true;
		}
		
		//if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].visibleSet == true)
		//{
		//	StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 464, 94, 92, B_VOID);
		//}
		//else
		//{
		//	StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 464, 94, 92, B_HOME);
		//}
		//// replay
		//if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->replayButtonId].visibleSet == true)
		//{
		//	StateMachine::GetInstance()->listButtons[B_REPLAY].SetProperty(319, 463, 94, 90, B_VOID);
		//}
		//else
		//{
		//	StateMachine::GetInstance()->listButtons[B_REPLAY].SetProperty(319, 463, 94, 90, B_REPLAY);
		//}

	}
	for (int i = 0; i<floorObj.size(); i++)
	{
		b2Vec2 vel = floorObj[i]->m_body->GetLinearVelocity();
		if (floorObj[i]->m_body->GetPosition().x < -m_floorWidth / 2 + 2)
		{
			vel.x = 5;
			((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(true);
		}
		else if (floorObj[i]->m_body->GetPosition().x > m_floorWidth / 2 - 2)
		{
			vel.x = -5;
			((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(false);
		}
		if (floorObj[i]->m_body == floorObj[(currentFloor) % 6]->m_body)
		{
			if (floorObj[i]->m_body->GetPosition().x < -m_floorWidth / 2 + 2)
			{
				vel.x = objSpeed;
				((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(true);
			}
			else if (floorObj[i]->m_body->GetPosition().x > m_floorWidth / 2 - 2)
			{
				vel.x = -objSpeed;
				((Object*)floorObj[i]->m_body->GetUserData())->SetFlip(false);
			}
		}
		floorObj[i]->m_body->SetLinearVelocity(vel);
	}
	if (currentFloor == m_inumOfFloor  && m_inumOfFloor != 0  )
	{
		if (lastFloor->m_body->GetPosition().x > -5)
		{
			lastFloor->m_body->SetLinearVelocity(b2Vec2(-3, 0));
			((Object*)lastFloor->m_body->GetUserData())->SetFlip(false);
		}
		else
		{
			((Object*)objBody->m_body->GetUserData())->SetVisible(true, 0);
			((Object*)lastFloor->m_body->GetUserData())->SetVisible(true, 0);
			
			static int old = currentTick;
			if (currentTick - old > 1000)
			{
				
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->maskId].SetVisible(false, 0);
				SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->winTextureId].SetVisible(false, 0);
				//SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(false, 0);
				//StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 464, 94, 92, B_HOME);
				//SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->nextButtonId].SetVisible(false, 0);
				//StateMachine::GetInstance()->listButtons[B_NEXT].SetProperty(319, 463, 94, 90, B_NEXT);
				if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].visibleSet == true)
				{
					SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->homeButtonId].SetVisible(false, 0);
					StateMachine::GetInstance()->listButtons[B_HOME].SetProperty(167, 464, 94, 92, B_HOME);
				}
				// next
				if (SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->nextButtonId].visibleSet == true)
				{
					SceneManager::GetInstance()->listObject[SceneManager::GetInstance()->nextButtonId].SetVisible(false, 0);
					StateMachine::GetInstance()->listButtons[B_NEXT].SetProperty(319, 463, 94, 90, B_NEXT);
				}
				winGame = true;
			}

		}
	}
	b2Body* b = m_world->GetBodyList();
	m_world->GetBodyCount();
	Object* listObject = SceneManager::GetInstance()->listObject;
	//while (b != NULL)
	while (b->GetUserData() != NULL)
	{
		if (b->GetType() == 0)
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth + 23);
		}
		if (b->GetType() == 1)
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth);
		}
		if (b->GetType() == 2)
		{
			((Object*)b->GetUserData())->SetPosition
			(b->GetPosition().x / 40 * SceneManager::GetInstance()->sceneWidth, b->GetPosition().y / 40 * SceneManager::GetInstance()->sceneWidth - 5);
		}
		b = b->GetNext();
	}
	m_button = false;
}

