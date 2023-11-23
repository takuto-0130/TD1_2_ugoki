#pragma once
#include "Vector2.h"
#include "FlyingParticle.h"
#include <list>


class FlyingEmitter
{
public:
	FlyingEmitter();
	~FlyingEmitter();

	void Update(Vector2 centerPos);
	void Draw();

	void Emit(float centerX, float centerY); // パーティクルの生成を行う関数

private:
	std::list<FlyingParticle> particleList;

	int timer_ = 0; // パーティクルを生成してからのフレーム数をカウント
	int interval_ = 4; // パーティクル生成の間隔
};

