#pragma once
#include "RunningParticle.h"
#include <list>
#include "particle/util/Util.h"

class RunningEmitter
{
public:
	RunningEmitter();
	~RunningEmitter();

	void Update(Vector2 pos, int jumpCount);
	void Draw();

	void Emit(Vector2 pos); //パーティクルを生成する関数

private:
	std::list<RunningParticle> particleList;

	int range_ = 7; //プレイヤーを9分割した際の左下のブロック（14*14）からパーティクルを生成するため、左下ブロックの中心から範囲を考えた際の値

	int timer_ = 0; // パーティクルを生成してからのフレーム数をカウント
	int interval_ = 1; // パーティクル生成の間隔
};
