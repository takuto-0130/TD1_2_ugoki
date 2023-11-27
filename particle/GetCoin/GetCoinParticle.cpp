#include "GetCoinParticle.h"

GetCoinParticle::GetCoinParticle(Vector2 pos, Vector2 velocity,float speed, unsigned int color)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	speed_ = speed;

	color_ = color;
}

GetCoinParticle::~GetCoinParticle()
{
}

void GetCoinParticle::Update()
{
	timer_++;

	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新
	pos_.x += velocity_.x * speed_;
	pos_.y += velocity_.y * speed_;

	// 粒の移動速度を時間経過で落としていく
	if (speed_ > 0) {
		speed_ -= 0.06f;
	}

	// 指定フレーム経過したらY方向に重力をかける
	if (timer_ > 16) {
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

void GetCoinParticle::Draw(int scroll)
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x) - scroll, static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x) - scroll, static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x) - scroll, static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x) - scroll, static_cast<int>(rightBottom_.y),
		0, 0,
		42, 42,
		gh_,
		color_ + alpha_
	);
}

bool GetCoinParticle::GetDelFlag()
{
	return del_;
}
