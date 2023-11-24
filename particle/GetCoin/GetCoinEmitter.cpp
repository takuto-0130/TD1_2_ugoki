#include "GetCoinEmitter.h"
#include "particle/util/Util.h"

GetCoinEmitter::GetCoinEmitter()
{
}

GetCoinEmitter::~GetCoinEmitter()
{
}

void GetCoinEmitter::Update()
{
	timer_++;

	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}

	// 1つ目の円の更新処理
	circleRadius_[0] += 2;

	if (circleAlpha_[0] > 0) {
		circleAlpha_[0] -= 4;
	}

	if (circleAlpha_[0] <= 0) {
		circleDel_[0] = true;
	}

	// 2つ目の円の更新処理
	if (timer_ > 8) {
		circleRadius_[1] += 2;

		if (circleAlpha_[1] > 0) {
			circleAlpha_[1] -= 4;
		}

		if (circleAlpha_[1] <= 0) {
			circleDel_[1] = true;
		}
	}
}

void GetCoinEmitter::Draw(int scroll)
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw(scroll);
	}

	// １つ目の円の描画
	if (circleDel_[0] == false) {
		Novice::DrawEllipse(
			static_cast<int>(circlePos_[0].x) - scroll, static_cast<int>(circlePos_[0].y),
			circleRadius_[0], circleRadius_[0],
			0.0f,
			0xFFFFFF00 + circleAlpha_[0], kFillModeSolid
		);
	}

	// 2つ目の円の描画
	if (timer_ > 8) {
		if (circleDel_[1] == false) {
			Novice::DrawEllipse(
				static_cast<int>(circlePos_[1].x) - scroll, static_cast<int>(circlePos_[1].y),
				circleRadius_[1], circleRadius_[1],
				0.0f,
				0xFFFFFF00 + circleAlpha_[1], kFillModeSolid
			);
		}
	}
}

void GetCoinEmitter::Emit(Vector2 centerPos)
{
	float angle_ = 45.0f * (float)M_PI / 180.f;

	// 外側の粒（スピードがちょっと速い）
	for (int i = 0; i < 8; i++) {
		float particleX = static_cast<float>(Random((int)centerPos.x - 10, (int)centerPos.x + 10));
		float particleY = static_cast<float>(Random((int)centerPos.y - 10, (int)centerPos.y + 10));

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		GetCoinParticle newParticle = GetCoinParticle({ particleX,particleY }, { velocityX,velocityY },6.0f);
		particleList.push_back(newParticle);
	}

	// 内側の粒（スピードがちょっと遅い）
	for (int i = 0; i < 8; i++) {
		float particleX = static_cast<float>(Random((int)centerPos.x - 10, (int)centerPos.x + 10));
		float particleY = static_cast<float>(Random((int)centerPos.y - 10, (int)centerPos.y + 10));

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		GetCoinParticle newParticle = GetCoinParticle({ particleX,particleY }, { velocityX,velocityY }, 4.0f);
		particleList.push_back(newParticle);
	}

	// 広がる円の初期化
	circlePos_[0] = { centerPos.x,centerPos.y };
	circlePos_[1] = { centerPos.x,centerPos.y };

	circleRadius_[0] = 30;
	circleRadius_[1] = 30;

	circleAlpha_[0] = 128;
	circleAlpha_[1] = 128;

	circleDel_[0] = false;
	circleDel_[1] = false;

	timer_ = 0;
}
