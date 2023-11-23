#include "ClearEmitter.h"

ClearEmitter::ClearEmitter()
{
}

ClearEmitter::~ClearEmitter()
{
}

void ClearEmitter::Update()
{
	// タイマーを進める
	timer_++;

	// 発生間隔をランダムで決める
	interval_ = Random(10, 20);

	if (timer_ % interval_ == 0) {
		Emit({ static_cast<float>(Random(centerX_ - rangeX_,centerX_ + rangeX_)),{static_cast<float>(Random(centerY_ - rangeY_,centerY_ + rangeY_))} });
	}

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
}

void ClearEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void ClearEmitter::Emit(Vector2 centerPos)
{
	float angle_ = 22.5f * (float)M_PI / 180.f; // 一度で16個生成するため
	float speed = static_cast<float>(Random(3, 4));

	for (int i = 0; i < 16; i++) {
		float particleX = centerPos.x;
		float particleY = centerPos.y;

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		float size = static_cast<float>(Random(10, 20));

		ClearParticle newParticle = ClearParticle({ particleX,particleY }, { velocityX,velocityY }, size,speed);
		particleList.push_back(newParticle);
	}
}
