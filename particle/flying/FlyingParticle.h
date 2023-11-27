#pragma once
#include <Novice.h>
#include "Vector2.h"

class FlyingParticle
{
public:
	FlyingParticle(Vector2 centerPos);
	~FlyingParticle();

	void Update();
	void Draw();

	bool GetDelFlag(); // パーティクルが消えているかを取得する

private:
	int gh_ = Novice::LoadTexture("./images/flyingParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 Velocity_ = { 8.0f,0.0f };
	float size_ = 42.0f;
	int alpha_ = 128;
	bool del_ = false;
	int green_ = 0;
};
