#pragma once
#include "jumpEnergyParticle.h"
#include <list>
#include "Vector2.h"
#include "particle/util/Util.h"
#define _USE_MATH_DEFINES
#include <math.h>

class JumpEnergyEmitter
{
public:
	JumpEnergyEmitter();
	~JumpEnergyEmitter();

	void Update(Vector2 pos, bool isJump, int life, bool isClear, int scene);
	void Draw();

	void Emit(Vector2 pos);//パーティクルを生成する関数
	void EmitGoal(Vector2 pos);

private:
	std::list<JumpEnergyParticle> particleList;

	int timer_ = 0; // パーティクルを生成してからのフレーム数をカウント
	const int kTimerMax_ = 40;
	int interval_ = 1; // パーティクル生成の間隔
	bool isEmit_ = 0;
};
