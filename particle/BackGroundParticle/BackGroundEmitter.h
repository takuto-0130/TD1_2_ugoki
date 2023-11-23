#pragma once
#include "BackGroundParticle.h"
#include <list>
#include "particle/util/Util.h"

class BackGroundEmitter
{
public:
	BackGroundEmitter();
	~BackGroundEmitter();

	void Update(Vector2 playerPos);
	void Draw(int scroll);

	void Emit(Vector2 playerPos);

private:
	std::list<BackGroundParticle> particleList;

	int leftRangeX_ = 400;
	int rightRangeX_ = 960 + 400; // プレイヤーが移動しているので余裕を持たせて右画面端 + 320の位置まで生成を行う

	int rangeY_ = 756;

	int timer_ = 0;
	int interval_ = 5;
};

