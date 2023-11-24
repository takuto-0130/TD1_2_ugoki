#pragma once
#include "ModeChangeParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

class ModeChangeEmitter
{
public:
	ModeChangeEmitter();
	~ModeChangeEmitter();

	void Update(Vector2 moveAmount);
	void Draw(int scroll);

	void Emit(Vector2 centerPos);

private:
	std::list<ModeChangeParticle> particleList;

	float radius_ = 40.0f; // プレイヤーの中心からの半径
};

