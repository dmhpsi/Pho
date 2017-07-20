#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	height = MID_CAM;
	position = Vector3(0, height, 4);
	target = Vector3(0, height, 3);
	up = Vector3(0, 1, 0);
	direction = 0;
	jumping = false;
	freeMode = false;

	R.SetTranslation(target.x, target.y, target.z + 1);
	T.SetTranslation(position.x, position.y, position.z);
}

Matrix Camera::ViewTheWorld()
{
	Matrix V;

	T.SetTranslation(position.x, position.y, position.z);
	R.SetTranslation(target.x, target.y, target.z + 1);
	
	Vector3 x, y, z;
	z = position - target;
	z.Normalize();
	x = up.Cross(z);
	x.Normalize();
	y = z.Cross(x);

	V.m[0][0] = x.x;              V.m[0][1] = y.x;              V.m[0][2] = z.x;              V.m[0][3] = 0.0f;
	V.m[1][0] = x.y;              V.m[1][1] = y.y;              V.m[1][2] = z.y;              V.m[1][3] = 0.0f;
	V.m[2][0] = x.z;              V.m[2][1] = y.z;              V.m[2][2] = z.z;              V.m[2][3] = 0.0f;
	V.m[3][0] = -x.Dot(position); V.m[3][1] = -y.Dot(position); V.m[3][2] = -z.Dot(position); V.m[3][3] = 1.0f;

	return V;
}

void Camera::LookLeft(GLfloat angle)
{
	Matrix Ry;
	Ry.SetRotationY(angle);

	Vector4 trans = Vector4(target.x - position.x, target.y - position.y, target.z - position.z, 1)*Ry;

	target.x += trans.x;
	target.y += trans.y;
	target.z += trans.z;

	R.SetTranslation(target.x, target.y, target.z + 1);
	//T.SetTranslation(position.x, position.y, position.z);
}

void Camera::LookUp(GLfloat angle)
{
	Vector3 look = (target - position).Normalize();
	GLfloat cosx = up.Dot(look);
			
	if ((cosx > -MAX_COS && cosx < MAX_COS) || (cosx >= MAX_COS && angle < 0) || (cosx <= -MAX_COS && angle > 0))
	{
		Matrix Rx;
		Rx.SetRotationX(angle);
		Vector4 localTar = Vector4(0, 0, -(position - target).Length(), 1);
		Vector4 localNew = localTar * Rx;
		Vector4 worldNew = localNew * R;

		target.x = worldNew.x;
		target.y = worldNew.y;
		target.z = worldNew.z;
	}

	R.SetTranslation(target.x, target.y, target.z + 1);
	//T.SetTranslation(position.x, position.y, position.z);
}

void Camera::MoveUp(GLfloat distance)
{
	Vector3 deltaMove = -(position - target).Normalize()*distance;
	position += deltaMove;
	target += deltaMove;

	R.SetTranslation(target.x, target.y, target.z + 1);
	T.SetTranslation(position.x, position.y, position.z);
}

void Camera::MoveLeft(GLfloat distance)
{
	Vector3 deltaMove = (position - target).Normalize()*distance;
	deltaMove = deltaMove.Cross(up);
	position += deltaMove;
	target += deltaMove;

	R.SetTranslation(target.x, target.y, target.z + 1);
	T.SetTranslation(position.x, position.y, position.z);
}

void Camera::Duck(bool set)
{
	if (set)
	{
		if (height > LOW_CAM)
			height -= 0.06;
	}
	else
	{
		if (height < MID_CAM)
			height += 0.06;
	}
}

void Camera::Reset()
{
	height = MID_CAM;
	position = Vector3(0, height, 4);
	target = Vector3(0, height, 3);
	up = Vector3(0, 1, 0);
	direction = 0;
	jumping = false;
	freeMode = false;

	R.SetTranslation(target.x, target.y, target.z + 1);
	T.SetTranslation(position.x, position.y, position.z);
}

void Camera::Act(MyEnum what, bool setOrRelease)
{
	if (setOrRelease)
	{
		direction |= what;
	}
	else
	{
		direction &= ~what;
	}
}

void Camera::Update(GLfloat deltaTime)
{
	float rush;
	static bool falling, jumpKey, duckKey;
	if (direction & RUSH)
	{
		rush = 2.0;
	}
	else
	{
		rush = 1.0;
	}

	if (direction & LOOK_UP)
		LookUp(SPEED*deltaTime);

	if (direction & LOOK_DOWN)
		LookUp(-SPEED*deltaTime);

	if (direction & LOOK_LEFT)
		LookLeft(SPEED*deltaTime * 3);

	if (direction & LOOK_RIGHT)
		LookLeft(-SPEED*deltaTime * 3);

	if (direction & MOVE_UP)
		MoveUp(SPEED*deltaTime * 5 * rush);

	if (direction & MOVE_DOWN)
		MoveUp(-SPEED*deltaTime * 5 * rush);

	if (direction & MOVE_LEFT)
		MoveLeft(SPEED*deltaTime * 5 * rush);

	if (direction & MOVE_RIGHT)
		MoveLeft(-SPEED*deltaTime * 5 * rush);
	
	if (direction & JUMPING)
	{
		if (!jumpKey)
		{
			if (!jumping)
			{
				jumping = true;
				falling = false;
			}
		}
		jumpKey = true;
	}
	else
	{
		jumpKey = false;
	}
	
	if (jumping)
	{
		if (!falling)
		{
			if (height >= (duckKey ? MID_CAM : HIGH_CAM))
			{
				falling = true;
			}
			else
			{
				height += 0.06;
			}
		}
		else
		{
			if (height <= (duckKey ? LOW_CAM : MID_CAM))
			{
				jumping = false;
			}
			else
			{
				height -= 0.06;
			}
		}
	}
	else
	{
		if (direction & DUCKING)
		{
			Duck(true);
			duckKey = true;
		}
		else
		{
			duckKey = false;
			Duck(false);
		}
	}

	if (direction & FREE_MODE)
	{
		direction &= ~FREE_MODE;
		freeMode = !freeMode;
		if (!freeMode)
			height = MID_CAM;
	}
	
	if (freeMode)
	{
		height = position.y;
	}

	if (direction & RESET)
		Reset();
	
	target.y += height - position.y;
	position.y = height;
		
	target = (target - position).Normalize() + position;

	R.SetTranslation(target.x, target.y, target.z + 1);
	T.SetTranslation(position.x, position.y, position.z);
}

Camera* Camera::Instance = 0;

Camera* Camera::GetInstance()
{
	if (!Instance)
	{
		Instance = new Camera();
	}
	return Instance;
}

void Camera::CleanInstance()
{
	delete Instance;
	Instance = NULL;
}

Camera::~Camera()
{

}