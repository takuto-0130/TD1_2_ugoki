#include "ModeChangeEmitter.h"

ModeChangeEmitter::ModeChangeEmitter()
{
}

ModeChangeEmitter::~ModeChangeEmitter()
{
}

void ModeChangeEmitter::Update(Vector2 moveAmount)
{
	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update(moveAmount);

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void ModeChangeEmitter::Draw(int scroll)
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw(scroll);
	}
}

void ModeChangeEmitter::Emit(Vector2 centerPos)
{
	float angle_ = 36.0f * (float)M_PI / 180.f;

	// 大きい粒を5個生成
	for (int i = 0; i < 10; i++) {
		float particleX = centerPos.x + radius_ * cosf(i * angle_);
		float particleY = centerPos.y + radius_ * sinf(i * angle_);

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		unsigned int color = 0x00000000;
		int R = 255;
		int G = Random(30, 120);
		int B = Random(30, 120);
		color += R << 24;
		color += G << 16;
		color += B << 8;

		ModeChangeParticle newParticle = ModeChangeParticle({ particleX,particleY }, { velocityX,velocityY },30.0f, color);
		particleList.push_back(newParticle);
	}

	// 小さい粒を5個生成
	for (int i = 0; i < 10; i++) {
		float particleX = centerPos.x + radius_ * cosf(36 + (i * angle_));
		float particleY = centerPos.y + radius_ * sinf(36 + (i * angle_));

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		unsigned int color = 0x00000000;
		int R = 255;
		int G = Random(200, 255);
		int B = Random(50, 150);
		color += R << 24;
		color += G << 16;
		color += B << 8;

		ModeChangeParticle newParticle = ModeChangeParticle({ particleX,particleY }, { velocityX,velocityY }, 20.0f, color);
		particleList.push_back(newParticle);
	}
}
