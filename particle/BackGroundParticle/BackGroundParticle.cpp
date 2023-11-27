#include "BackGroundParticle.h"
#include "Matrix/Matrix.h"

BackGroundParticle::BackGroundParticle(Vector2 pos, Vector2 velocity, unsigned int color)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;

	color_ = color;
}

BackGroundParticle::~BackGroundParticle()
{
}

void BackGroundParticle::Update()
{
	// 4頂点の座標を更新（原点を中心に考える）
	leftTop_ = { -size_ / 2,-size_ / 2 };
	rightTop_ = { size_ / 2,-size_ / 2 };
	leftBottom_ = { -size_ / 2,size_ / 2 };
	rightBottom_ = { size_ / 2,size_ / 2 };

	// 角度を毎フレーム増加
	theta_ += (2.0f * (float)M_PI) / 180.0f;

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

	// 座標の移動を行う（Y座標のみ）
	/*pos_.y += velocity_.y;*/

	// 徐々に透明にする
	if (alpha_ > 0) {
		alpha_ -= 4;
	}

	// サイズを小さくする
	if (size_ >= 0) {
		size_ -= 0.3f;
	}

	// サイズが0になったら削除
	if (size_ < 0) {
		del_ = true;
	}
}

void BackGroundParticle::Draw(int scroll)
{
	Novice::DrawQuad(
		static_cast<int>(movedLeftTop.x) - scroll, static_cast<int>(movedLeftTop.y),
		static_cast<int>(movedRightTop.x) - scroll, static_cast<int>(movedRightTop.y),
		static_cast<int>(movedLeftBottom.x) - scroll, static_cast<int>(movedLeftBottom.y),
		static_cast<int>(movedRightBottom.x) - scroll, static_cast<int>(movedRightBottom.y),
		0, 0,
		1, 1,
		gh_,
		color_ + alpha_
	);
}

bool BackGroundParticle::GetDelFlag()
{
	return del_;
}
