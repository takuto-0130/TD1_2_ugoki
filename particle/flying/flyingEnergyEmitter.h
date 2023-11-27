#pragma once
#include "flyingEnergyParticle.h"
#include <list>
#include "Vector2.h"
#include "particle/util/Util.h"
#define _USE_MATH_DEFINES
#include <math.h>

class FlyingEnergyEmitter
{
public:
	FlyingEnergyEmitter();
	~FlyingEnergyEmitter();

	void Update(Vector2 pos, bool isArea, int life);
	void Draw();

	void Emit(Vector2 pos);//パーティクルを生成する関数
	void EmitGoal(Vector2 pos);

private:
	std::list<FlyingEnergyParticle> particleList;

	int timer_ = 0; // パーティクルを生成してからのフレーム数をカウント
	int interval_ = 1; // パーティクル生成の間隔
};
