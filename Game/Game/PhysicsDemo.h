#pragma once
#include "../NewTrainingFramework/NewTrainingFramework.h"

class NewObj :public Object
{
public:
	NewObj();
	NewObj(Object &obj);
	float sx, sy, an, speed;
	void Update(float ms);
};
