#include "jumpEnergyParticle.h"
#define _USE_MATH_DEFINES
#include <math.h>

JumpEnergyParticle::JumpEnergyParticle(Vector2 pos, Vector2 angle, float size)
{
	goalPos_ = pos;
	startAngle_.x = (distance_ * angle.x);
	startAngle_.y = (distance_ * angle.y);
	size_ = size;
	startPos_.x = pos.x + startAngle_.x;
	startPos_.y = pos.y + startAngle_.y;
}

JumpEnergyParticle::~JumpEnergyParticle()
{
}

void JumpEnergyParticle::EmitGoal(Vector2 pos)
{
	goalPos_ = pos;
}

void JumpEnergyParticle::Update()
{
	// 生成されてからのタイマーを増やす
	timer_++;

	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	float ease = 0;

	ease = powf(timer_ / kTimerMax_, 3);

	pos_.x = startPos_.x + ((goalPos_.x - startPos_.x) * ease);
	pos_.y = startPos_.y + ((goalPos_.y - startPos_.y) * ease);

	if (timer_ >= kTimerMax_) {
		del_ = true;
	}
}

void JumpEnergyParticle::Draw()
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x), static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x), static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x), static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x), static_cast<int>(rightBottom_.y),
		0, 0,
		1, 1,
		gh_,
		0xFFFFFFFF
	);
}

bool JumpEnergyParticle::GetDelFlag()
{
	return del_;
}