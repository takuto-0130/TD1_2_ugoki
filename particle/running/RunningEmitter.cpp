#include "RunningEmitter.h"

RunningEmitter::RunningEmitter()
{
}

RunningEmitter::~RunningEmitter()
{
}

void RunningEmitter::Update(Vector2 pos, int jumpCount)
{
	// タイマーを進める
	timer_++;

	// 設定した間隔毎にパーティクルを生成する
	if (timer_ % interval_ == 0 && jumpCount == 0) {
		RunningEmitter::Emit({ pos.x,pos.y });
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

void RunningEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void RunningEmitter::Emit(Vector2 pos)
{
	// エミッター範囲内で座標をランダムに設定
	float particleX = static_cast<float>(Random((int)pos.x - range_, (int)pos.x + range_));
	float particleY = static_cast<float>(Random((int)pos.y - range_, (int)pos.y + range_));

	// 速度をランダムに設定
	float velocityX = static_cast<float>(Random(6, 8));
	float velocityY = static_cast<float>(Random(0, 2));

	// サイズをランダムに設定
	float size = static_cast<float>(Random(5, 10));

	// ランダムに設定した数値を生成したパーティクルに格納
	RunningParticle newParticle = RunningParticle({ particleX,particleY }, { velocityX,velocityY }, size);
	particleList.push_back(newParticle);
}
