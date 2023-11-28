#include "PlayerDeadParticle.h"

PlayerDeadParticle::PlayerDeadParticle(Vector2 pos, Vector2 velocity, float size, unsigned int color)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	size_ = size;

	color_ = color;
}

PlayerDeadParticle::~PlayerDeadParticle()
{

}

void PlayerDeadParticle::Update()
{
	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新
	pos_.x += velocity_.x;
	pos_.y += velocity_.y;

	// 徐々に透明にする
	if (alpha_ > 0) {
		alpha_ -= 4;
	}

	// サイズを小さくする
	if (size_ >= 0) {
		size_ -= 0.6f;
	}

	// サイズが0になったら削除
	if (size_ < 0) {
		del_ = true;
	}
}

void PlayerDeadParticle::Draw()
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x), static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x), static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x), static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x), static_cast<int>(rightBottom_.y),
		0, 0,
		1, 1,
		gh_,
		color_ + alpha_
	);
}

bool PlayerDeadParticle::GetDelFlag()
{
	return del_;
}
