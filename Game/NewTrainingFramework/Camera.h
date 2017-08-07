#pragma once
#include "define.h"
#include "../Utilities/utilities.h"
#include <math.h>

class Camera
{
	Vector3 position, target, up;
	Matrix T, R, W, O;
	int direction;
	static Camera* Instance;
	float height, targetHeight, moveSpeed, acce;
	~Camera();
	bool jumping;
	bool freeMode;
public:
	Camera();
	float speed;
	static Camera* GetInstance();
	static void CleanInstance();
	void Act(MyEnum what, bool set);
	void Update(GLfloat deltaTime);
	void LookLeft(GLfloat angle);
	void LookUp(GLfloat angle);
	void MoveUp(GLfloat distance);
	void MoveLeft(GLfloat distance);
	void SetOrtho(float l, float r, float b, float t, float n, float f);
	Matrix GetAbsoluteViewMatrix();

	// Set height of camera base on current floor height
	void SetHeight(float y, float ms);
	void Duck(bool set);
	void Reset();
	Matrix ViewTheWorld();
};
