#pragma once
#include<Vector2.h>
#include<Novice.h>

class PlayerDeadParticle
{
public:
	PlayerDeadParticle(Vector2 pos,Vector2 velocity,float size, unsigned int color);
	~PlayerDeadParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/backGroundParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float size_;
	int alpha_ = 192;
	bool del_ = false;
	unsigned int color_;
};

