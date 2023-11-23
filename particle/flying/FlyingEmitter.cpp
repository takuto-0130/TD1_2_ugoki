#include "FlyingEmitter.h"

FlyingEmitter::FlyingEmitter()
{
}

FlyingEmitter::~FlyingEmitter()
{
}

void FlyingEmitter::Update(Vector2 centerPos)
{
	// タイマーを進める
	timer_++;

	// 設定した間隔毎にパーティクルを生成
	if (timer_ % interval_ == 0) {
		FlyingEmitter::Emit(centerPos.x, centerPos.y);
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

void FlyingEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void FlyingEmitter::Emit(float centerX, float centerY)
{
	float particleX = centerX;
	float particleY = centerY;

	FlyingParticle newParticle = FlyingParticle({ particleX,particleY });
	particleList.push_back(newParticle);
}
