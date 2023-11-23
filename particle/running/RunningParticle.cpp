#include "RunningParticle.h"

RunningParticle::RunningParticle(Vector2 pos, Vector2 velocity, float size)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	size_ = size;
}

RunningParticle::~RunningParticle()
{
}

void RunningParticle::Update()
{
	// 生成されてからのタイマーを増やす
	timer_++;

	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 移動処理
	pos_.x -= velocity_.x;
	pos_.y -= velocity_.y;

	// 生成されてからxxフレーム経過したパーティクルに重力加速度を加算する
	if (timer_ >= 6) {
		velocity_.y -= acceleratorY_;
	}

	// 透明にしていく処理
	if (alpha_ > 0) {
		alpha_ -= 1;
	}

	// サイズを小さくしていく処理
	if (size_ > 0.0f) {
		size_ -= 0.3f;
	}

	// サイズが0になったら削除
	if (size_ < 0.0f) {
		del_ = true;
	}
}

void RunningParticle::Draw()
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x), static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x), static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x), static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x), static_cast<int>(rightBottom_.y),
		0, 0,
		1, 1,
		gh_,
		0xFFFFFF00 + alpha_
	);
}

bool RunningParticle::GetDelFlag()
{
	return del_;
}
