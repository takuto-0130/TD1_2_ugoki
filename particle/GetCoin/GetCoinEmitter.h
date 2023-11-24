#pragma once
#include "Vector2.h"
#include "GetCoinParticle.h"
#include <list>
#include "particle/util/Util.h"
#define _USE_MATH_DEFINES
#include <math.h>

class GetCoinEmitter
{
public:
	GetCoinEmitter();
	~GetCoinEmitter();

	void Update();
	void Draw(int scroll);

	void Emit(Vector2 centerPos);

private:
	std::list<GetCoinParticle> particleList;

	// 広がる円
	Vector2 circlePos_[2];
	int circleRadius_[2];
	int circleAlpha_[2];
	bool circleDel_[2] = { false,false };

	int timer_ = 0;
};

