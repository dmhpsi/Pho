#include "stdafx.h"
#include "Button.h"

bool Button::IsInside(float mouse_x, float mouse_y)
{
	return (type != B_VOID) 
		&& (mouse_x < x + w / 2) 
		&& (mouse_x > x - w / 2) 
		&& (mouse_y < y + h / 2) 
		&& (mouse_y > y - h / 2);
}

void Button::SetProperty(float x, float y, float w, float h, MyEnum type)
{
	Button::x = x;
	Button::y = y;
	Button::w = w;
	Button::h = h;
	Button::type = type;
}

Button::Button()
{
	x = y = w = h = 0;
	type = B_VOID;
}
