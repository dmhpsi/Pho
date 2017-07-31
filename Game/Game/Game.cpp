// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../NewTrainingFramework/NewTrainingFramework.h"

<<<<<<< HEAD
extern sf::Music* b;
=======
>>>>>>> dmhpsi/huynx
int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

<<<<<<< HEAD
	esCreateWindow(&esContext, "Pho", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
=======
	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
>>>>>>> dmhpsi/huynx

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
<<<<<<< HEAD
	esRegisterMouseDownFunc(&esContext, OnMouseDown);
	esRegisterMouseUpFunc(&esContext, OnMouseUp);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);
=======
>>>>>>> dmhpsi/huynx

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
<<<<<<< HEAD
	
=======
>>>>>>> dmhpsi/huynx
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}