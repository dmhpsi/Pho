#pragma once

#include "Box2D/Box2D.h"
#include "Testbed\Framework\Test.h"
#include <stdio.h>

class Play
{
public:
	void Playgame();
	void handleInput();
	void update(float dt);
	void render();
};
