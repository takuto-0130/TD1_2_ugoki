﻿#include "CheckPointParticle.h"
#include "Matrix/Matrix.h"

CheckPointParticle::CheckPointParticle(Vector2 pos, Vector2 velocity, float size, unsigned int color)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	size_ = size;

	color_ = color;
}

CheckPointParticle::~CheckPointParticle()
{
}

void CheckPointParticle::Update()
{
	timer_++;

	// 4頂点の座標を更新（原点を中心に考える）
	leftTop_ = { (float)-size_ / 2,(float)-size_ / 2 };
	rightTop_ = { (float)size_ / 2,(float)-size_ / 2 };
	leftBottom_ = { (float)-size_ / 2,(float)size_ / 2 };
	rightBottom_ = { (float)size_ / 2,(float)size_ / 2 };

	// 座標を更新
	pos_.x += velocity_.x * speed_;
	pos_.y += velocity_.y * speed_;

	// 角度を毎フレーム増加
	theta_ += (4.0f * (float)M_PI) / 180.0f;

	// 回転行列を作成
	Matrix2x2 rotateMatrix = MakeRotateMatrix(theta_);

	// 4頂点を全て回転させる
	rotatedLeftTop = Multiply(leftTop_, rotateMatrix);
	rotatedRightTop = Multiply(rightTop_, rotateMatrix);
	rotatedLeftBottom = Multiply(leftBottom_, rotateMatrix);
	rotatedRightBottom = Multiply(rightBottom_, rotateMatrix);

	// 4頂点を移動させる
	movedLeftTop = { rotatedLeftTop.x + pos_.x ,rotatedLeftTop.y + pos_.y };
	movedRightTop = { rotatedRightTop.x + pos_.x,rotatedRightTop.y + pos_.y };
	movedLeftBottom = { rotatedLeftBottom.x + pos_.x,rotatedLeftBottom.y + pos_.y };
	movedRightBottom = { rotatedRightBottom.x + pos_.x,rotatedRightBottom.y + pos_.y };

	//// 色を薄くする
	//if (alpha_ > 0) {
	//	alpha_ -= 5;
	//}

	// 指定したスピードになるまで毎フレーム減らす
	if (speed_ > 1.5f) {
		speed_ -= 0.2f;
	}

	// 指定フレームに到達したら重力落下を始める
	if (timer_ > 12) {
		velocity_.y += acceleratorY;
	}

	size_ -= 0.8f;

	if (size_ <= 0) {
		del_ = true;
	}
}

void CheckPointParticle::Draw(int scroll)
{
	if (del_ == false) {
		Novice::DrawQuad(
			static_cast<int>(movedLeftTop.x) - scroll, static_cast<int>(movedLeftTop.y),
			static_cast<int>(movedRightTop.x) - scroll, static_cast<int>(movedRightTop.y),
			static_cast<int>(movedLeftBottom.x) - scroll, static_cast<int>(movedLeftBottom.y),
			static_cast<int>(movedRightBottom.x) - scroll, static_cast<int>(movedRightBottom.y),
			0, 0,
			42, 42,
			gh_,
			color_ + alpha_
		);
	}
}

bool CheckPointParticle::GetDelFlag()
{
	return false;
}
