#include "BackGroundEmitter.h"

BackGroundEmitter::BackGroundEmitter()
{
}

BackGroundEmitter::~BackGroundEmitter()
{
}

void BackGroundEmitter::Update(Vector2 playerPos)
{
	timer_++;

	if (timer_ % interval_ == 0) {
		BackGroundEmitter::Emit(playerPos);
	}

	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		}
		else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void BackGroundEmitter::Draw(int scroll)
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw(scroll);
	}
}

void BackGroundEmitter::Emit(Vector2 playerPos)
{
	// 画面内にのみパーティクルの生成を行うための制限
	float particleX = static_cast<float>(Random((int)playerPos.x - leftRangeX_, (int)playerPos.x + rightRangeX_));
	float particleY = static_cast<float>(Random(0, rangeY_));

	float velocityX = 0;
	float velocityY = static_cast<float>(Random(-1, 1));

	unsigned int color = 0x00000000;
	int R = Random(30, 100);
	int G = 255;
	int B = Random(30, 100);
	color += R << 24;
	color += G << 16;
	color += B << 8;

	BackGroundParticle newParticle = BackGroundParticle({ particleX,particleY }, { velocityX,velocityY }, color);
	particleList.push_back(newParticle);
}
