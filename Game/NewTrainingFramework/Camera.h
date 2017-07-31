#pragma once
#include "define.h"
#include "../Utilities/utilities.h"

class Camera
{
	Vector3 position, target, up;
<<<<<<< HEAD
	Matrix T, R, W, O;
=======
	Matrix T, R, W;
>>>>>>> dmhpsi/huynx
	int direction;
	static Camera* Instance;
	float height;
	~Camera();
	bool jumping;
	bool freeMode;
public:
	Camera();
<<<<<<< HEAD
	float speed;
=======
>>>>>>> dmhpsi/huynx
	static Camera* GetInstance();
	static void CleanInstance();
	void Act(MyEnum what, bool set);
	void Update(GLfloat deltaTime);
	void LookLeft(GLfloat angle);
	void LookUp(GLfloat angle);
	void MoveUp(GLfloat distance);
	void MoveLeft(GLfloat distance);
<<<<<<< HEAD
	void SetOrtho(float l, float r, float b, float t, float n, float f);
=======
>>>>>>> dmhpsi/huynx
	void Duck(bool set);
	void Reset();
	Matrix ViewTheWorld();
};
