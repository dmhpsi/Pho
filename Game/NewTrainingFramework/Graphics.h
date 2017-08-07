#pragma once
#include "define.h"

class Graphics
{
private:
	static Graphics* Instance;
	void(*DrawCallback)();
	void(*UpdateCallback)(float);
	void(*KeyCallback)(unsigned char, bool);
	void(*MouseDownCallback)(float, float);
	void(*MouseUpCallback)(float, float);
	void(*MouseMoveCallback)(float, float);
public:
	Graphics();
	static Graphics* GetInstance();
	static void CleanInstance();
	~Graphics();
	void RegisterDrawCallback(void(*funcName)());
	void RegisterUpdateCallback(void(*funcName)(float));
	void RegisterKeyCallback(void(*funcName)(unsigned char, bool));
	void RegisterMouseCallback(MyEnum funcType, void(*funcName)(float, float));
	void Draw();
	void Update(float);
	void Key(unsigned char, bool);
	void MouseDown(float, float);
	void MouseUp(float, float);
	void MouseMove(float, float);
};