#pragma once
#include <vector>
#include <string.h>
#include "..\NewTrainingFramework\SceneManager.h"
#include "..\NewTrainingFramework\NewTrainingFramework.h"
#include "..\Game\PhysicManager.h"
#include "..\Game\Button.h"

class StateMachine {
public:
	long  currentTime, lastTime;
	int currentLevel = 0;
	static StateMachine * Instance;
	static StateMachine * GetInstance();
	std::vector<Sound*> sounds;
	StateMachine();
	void Init();
	void LoadingInit();
	void MenuInit();
	void OptionMenuInit();
	void GamePlayInit();
	void DeleteState();
	void GameReturn();
	void LevelsInit();
	void Update(float deltaTime);
	void LoadingUpdate(float deltaTime);
	void MenuUpdate(float deltaTime);
	void GamePlayUpdate(float deltaTime);
	void Render();
	Button listButtons[20];
	
	~StateMachine();	
	enum GameState {
		GS_LOADING,
		GS_MAINMENU,
		GS_LEVELS,
		GS_GAME_RETURN,
		GS_GAMEPLAY,
		GS_OPTIONMENU,
		GS_CREDIT
	};
	GameState currentState;
	void ChangeState(GameState state);
	//void OnMouseUp(float x, float y);
	bool OnMouseDown(float x, float y);
	//void OnMouseMove(float x, float y);

};