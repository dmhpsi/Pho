#include "stdafx.h"
#include "Graphics.h"

Graphics* Graphics::Instance = 0;

Graphics* Graphics::GetInstance()
{
	if (!Instance)
	{
		Instance = new Graphics();
	}
	return Instance;
}

void Graphics::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}

Graphics::Graphics()
{
	DrawCallback = NULL;
	UpdateCallback = NULL;
	KeyCallback = NULL;
	MouseDownCallback = NULL;
	MouseUpCallback = NULL;
	MouseMoveCallback = NULL;
}

void Graphics::RegisterDrawCallback(void(*funcName)())
{
	DrawCallback = funcName;
}

void Graphics::RegisterUpdateCallback(void(*funcName)(float))
{
	UpdateCallback = funcName;
}

void Graphics::RegisterKeyCallback(void(*funcName)(unsigned char, bool))
{
	KeyCallback = funcName;
}

void Graphics::RegisterMouseCallback(MyEnum funcType, void(*funcName)(float, float))
{
	if (funcType == FUNC_MOUSEDOWN)
	{
		MouseDownCallback = funcName;
	}
	else if (funcType == FUNC_MOUSEUP)
	{
		MouseUpCallback = funcName;
	}
	else if (funcType == FUNC_MOUSEMOVE)
	{
		MouseMoveCallback = funcName;
	}
}

void Graphics::Draw()
{
	if (DrawCallback != NULL)
	{
		DrawCallback();
	}
}

void Graphics::Update(float delta)
{
	if (UpdateCallback != NULL)
	{
		UpdateCallback(delta);
	}
}

void Graphics::Key(unsigned char key, bool isPressed)
{
	if (KeyCallback != NULL)
	{
		KeyCallback(key, isPressed);
	}
}

void Graphics::MouseDown(float x, float y)
{
	if (MouseDownCallback != NULL)
	{
		MouseDownCallback(x, y);
	}
}

void Graphics::MouseUp(float x, float y)
{
	if (MouseUpCallback != NULL)
	{
		MouseUpCallback(x, y);
	}
}

void Graphics::MouseMove(float x, float y)
{
	if (MouseMoveCallback != NULL)
	{
		MouseMoveCallback(x, y);
	}
}

Graphics::~Graphics()
{
}
