#pragma once
#include<Vector2.h>
#include<Novice.h>

class GetCoinParticle
{
public:
	GetCoinParticle(Vector2 pos,Vector2 velocity,float speed);
	~GetCoinParticle();

	void Update();
	void Draw(int scroll);

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/GetCoinParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float acceleratorY = 0.07f;
	float size_ = 30.0f;
	float speed_;
	int alpha_ = 192;
	bool del_ = false;
	int timer_ = 0;
};

