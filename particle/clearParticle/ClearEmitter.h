#pragma once
#include "Vector2.h"
#include "ClearParticle.h"
#include <list>
#include "particle/util/Util.h"
#define _USE_MATH_DEFINES
#include <math.h>

class ClearEmitter
{
public:
	ClearEmitter();
	~ClearEmitter();

	void Update();
	void Draw();

	void Emit(Vector2 centerPos); // パーティクルの生成を行う

private:
	std::list<ClearParticle> particleList;

	int timer_ = 0; // パーティクルを生成してからのフレーム数をカウント
	int interval_; // パーティクル生成の間隔

	// パーティクルの発生範囲
	int centerX_ = 640;
	int centerY_ = 360;

	int rangeX_ = 540;
	int rangeY_ = 260;
};

