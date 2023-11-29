#pragma once
#include<Novice.h>
#include<Vector2.h>

class RunningParticle
{
public:
	RunningParticle(Vector2 pos, Vector2 velocity, float size);
	~RunningParticle();

	void Update();
	void Draw();

	bool GetDelFlag(); // パーティクルが消えたかを取得する関数

private:
	int gh_ = Novice::LoadTexture("./images/backGroundParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float acceleratorY_ = 0.1f;
	float size_;
	int alpha_ = 128;
	bool del_ = false;
	int timer_ = 0; //生成されてからのフレームをカウントするタイマー
};
