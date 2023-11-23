#pragma once
#include "PlayerDeadParticle.h"
#include <list>

class PlayerDeadEmitter
{
public:
	PlayerDeadEmitter();
	~PlayerDeadEmitter();

	void Update();
	void Draw();

	void Emit(Vector2 pos); //パーティクルの生成を行う関数

private:
	std::list<PlayerDeadParticle> particleList;

	int range_ = 4; // 中心座標からのパーティクルの出現範囲半径

	// 広がる円の情報
	Vector2 circlePos_;
	int circleRadius_;
	int circleAlpha_;
	bool circleDel_ = false;
};

