#include "CheckPointEmitter.h"

CheckPointEmitter::CheckPointEmitter()
{
}

CheckPointEmitter::~CheckPointEmitter()
{
}

void CheckPointEmitter::Update()
{
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

void CheckPointEmitter::Draw(int scroll)
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw(scroll);
	}
}

void CheckPointEmitter::Emit(Vector2 centerPos)
{

	// 大きい粒を4個生成
	for (int i = 0; i < 4; i++) {
		float angle_ = i * 90.0f * (float)M_PI / 180.f;

		float particleX = centerPos.x;
		float particleY = centerPos.y;

		float velocityX = 1 * cosf(angle_) - 0 * sinf(angle_);
		float velocityY = 1 * sinf(angle_) + 0 * cosf(angle_);

		unsigned int color = 0x00000000;
		int R = 255;
		int G = Random(40, 150);
		int B = Random(40, 150);
		color += R << 24;
		color += G << 16;
		color += B << 8;

		CheckPointParticle newParticle = CheckPointParticle({ particleX,particleY }, { velocityX,velocityY }, 40.0f, color);
		particleList.push_back(newParticle);
	}


	// 小さい粒を4個生成
	for (int i = 0; i < 4; i++) {
		float angle_ = (45.0f + (i * 90.0f)) * (float)M_PI / 180.f;
		float particleX = centerPos.x;
		float particleY = centerPos.y;

		float velocityX = 1 * cosf(angle_) - 0 * sinf(angle_);
		float velocityY = 1 * sinf(angle_) + 0 * cosf(angle_);

		unsigned int color = 0x00000000;
		int R = 255;
		int G = Random(170, 225);
		int B = Random(0, 150);
		color += R << 24;
		color += G << 16;
		color += B << 8;

		CheckPointParticle newParticle = CheckPointParticle({ particleX,particleY }, { velocityX,velocityY }, 30.0f, color);
		particleList.push_back(newParticle);
	}
}
