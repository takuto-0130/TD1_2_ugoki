#pragma once
#include<Vector2.h>
#include<Novice.h>

class BackGroundParticle
{
public:
	BackGroundParticle(Vector2 pos, Vector2 velocity);
	~BackGroundParticle();

	void Update();
	void Draw(int scroll);

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/backGroundParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 rotatedLeftTop = { 0.0f,0.0f };
	Vector2 rotatedRightTop = { 0.0f,0.0f };
	Vector2 rotatedLeftBottom = { 0.0f,0.0f };
	Vector2 rotatedRightBottom = { 0.0f,0.0f };

	Vector2 movedLeftTop = { 0.0f,0.0f };
	Vector2 movedRightTop = { 0.0f,0.0f };
	Vector2 movedLeftBottom = { 0.0f,0.0f };
	Vector2 movedRightBottom = { 0.0f,0.0f };

	Vector2 velocity_;
	float size_ = 16;
	int alpha_ = 192;
	bool del_ = false;

	float theta_ = 0.0f;
};

