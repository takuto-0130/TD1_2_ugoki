#pragma once
#include<Novice.h>
#include "Vector2.h"

class ClearParticle
{
public:
	ClearParticle(Vector2 pos, Vector2 velocity, float size,float speed);
	~ClearParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/clearParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float acceleratorY = 0.04f;
	float size_;
	float speed_;
	int alpha_ = 192;
	bool del_ = false;
	int timer_ = 0;
};

