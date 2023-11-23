#include "FlyingParticle.h"

FlyingParticle::FlyingParticle(Vector2 centerPos)
{
	pos_.x = centerPos.x;
	pos_.y = centerPos.y;
}

FlyingParticle::~FlyingParticle()
{
}

void FlyingParticle::Update()
{
	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 移動処理
	pos_.x -= Velocity_.x;

	// サイズを小さくしていく処理
	size_ -= 1.5f;

	// 透明にしていく処理
	if (alpha_ > 0) {
		alpha_ -= 4;
	}
	else {
		del_ = true;
	}
}

void FlyingParticle::Draw()
{
	if (alpha_ > 0 && size_ > 0) {
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
}

bool FlyingParticle::GetDelFlag()
{
	return del_;
}
