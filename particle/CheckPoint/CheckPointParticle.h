#pragma once
#include "Vector2.h"
#include <Novice.h>

class CheckPointParticle
{
public:
	CheckPointParticle(Vector2 pos, Vector2 velocity, float size, unsigned int color);
	~CheckPointParticle();

	void Update();
	void Draw(int scroll);

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/CheckPointParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	float theta_ = 0.0f;

	Vector2 rotatedLeftTop = { 0.0f,0.0f };
	Vector2 rotatedRightTop = { 0.0f,0.0f };
	Vector2 rotatedLeftBottom = { 0.0f,0.0f };
	Vector2 rotatedRightBottom = { 0.0f,0.0f };

	Vector2 movedLeftTop = { 0.0f,0.0f };
	Vector2 movedRightTop = { 0.0f,0.0f };
	Vector2 movedLeftBottom = { 0.0f,0.0f };
	Vector2 movedRightBottom = { 0.0f,0.0f };

	Vector2 velocity_;
	float speed_ = 6.0f;
	float acceleratorY = 0.08f;
	bool del_ = false;
	float size_;
	int alpha_ = 255;
	int timer_ = 0;
	unsigned int color_;
};

