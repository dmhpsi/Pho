// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../NewTrainingFramework/NewTrainingFramework.h"

extern sf::Music* b;
int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Pho", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, OnMouseDown);
	esRegisterMouseUpFunc(&esContext, OnMouseUp);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}