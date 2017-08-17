#pragma once
#include "../NewTrainingFramework/define.h"

class Button
{
	float x, y, w, h;
public:
	MyEnum type;
	bool IsInside(float mouse_x, float mouse_y);
	void SetProperty(float x, float y, float w, float h, MyEnum type);
	Button();
};