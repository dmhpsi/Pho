#pragma once
#include "Box2D/Box2D.h"
#define	RAND_LIMIT	32767

const int16	k_smallGroup = 1;
const int16 k_largeGroup = -1;
const float m_floorHeight = 17.5f;
const float m_floorWidth = 40.0f;
inline float32 RandomFloat()
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = 2.0f * r - 1.0f;
	return r;
}

/// Random floating point number in range [lo, hi]
inline float32 RandomFloat(float32 lo, float32 hi)
{
	float32 r = (float32)(rand() & (RAND_LIMIT));
	r /= RAND_LIMIT;
	r = (hi - lo) * r + lo;
	return r;
}