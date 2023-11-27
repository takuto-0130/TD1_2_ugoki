#pragma once
#include<Novice.h>
#include "Vector2.h"

class FlyingEnergyParticle
{
public:
	FlyingEnergyParticle(Vector2 pos, Vector2 angle, float size, unsigned int color);
	~FlyingEnergyParticle();

	void Update();
	void Draw();
	void EmitGoal(Vector2 pos);

	bool GetDelFlag(); // パーティクルが消えたかを取得する関数

private:
	int gh_ = Novice::LoadTexture("./images/jumpEnergy.png");

	Vector2 pos_; // 中心座標
	Vector2 startPos_;// パーティクルの出始めの中心座標
	Vector2 goalPos_;// パーティクルの終わりの中心座標
	Vector2 startAngle_;

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	float distance_ = 70;
	float size_;
	bool del_ = false;
	float timer_ = 0; //生成されてからのフレームをカウントするタイマー
	const float kTimerMax_ = 30;
	unsigned int color_;
};


