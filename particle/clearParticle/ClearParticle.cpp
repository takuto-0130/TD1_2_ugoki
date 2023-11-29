#include "ClearParticle.h"

ClearParticle::ClearParticle(Vector2 pos, Vector2 velocity, float size, float speed, unsigned int color)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	size_ = size;
	speed_ = speed;
	color_ = color;
}

ClearParticle::~ClearParticle()
{
}

void ClearParticle::Update()
{
	// タイマーを進める
	timer_++;

	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新
	pos_.x += velocity_.x * speed_;
	pos_.y += velocity_.y * speed_;

	// 指定フレーム経過したらY方向に重力をかける
	if (timer_ > 3) {
		velocity_.y += acceleratorY;
	}

	// 徐々に透明にする
	if (alpha_ > 0) {
		alpha_ -= 4;
	}

	// サイズを小さくする
	if (size_ >= 0) {
		size_ -= 0.2f;
	}

	// サイズが0になったら削除
	if (size_ < 0) {
		del_ = true;
	}
}

void ClearParticle::Draw()
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x), static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x), static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x), static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x), static_cast<int>(rightBottom_.y),
		0, 0,
		42, 42,
		gh_,
		color_ + alpha_
	);
}

bool ClearParticle::GetDelFlag()
{
	return del_;
}
